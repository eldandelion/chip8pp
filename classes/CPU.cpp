//
// Created by Daniel on 2024/8/23.
//

#include "CPU.h"
#include "iostream"

#include <cstdlib>
#include <ctime>

using std::cout;

void CPU::init() {


    PC = 0x0200;
    SP = 0xEFF;


}

void CPU::fetch_opcode() {

    unsigned char opcode_p1 = bus->read(PC);
    unsigned char opcode_p2 = bus->read(PC + 1);

    //  std::cout << "Opcode P1: 0x" << std::hex << static_cast<int>(opcode_p1) << std::endl;
    //  std::cout << "Opcode P2: 0x" << std::hex << static_cast<int>(opcode_p2) << std::endl;

    opcode = opcode_p1 << 8 | opcode_p2;

    //std::cout << "Opcode: 0x" << std::hex << static_cast<int>(opcode) << std::endl;

    decode_opcode();

}

CPU::CPU(BUS *bus, Graphics *graphics, Input *input) : bus(bus), graphics(graphics), input(input) {}

void CPU::decode_opcode() {

    switch (opcode & 0xF000) {
        case 0x0000: {


            switch (opcode & 0x00FF) {

                case 0x00E0: {
                    graphics->clear();

                    break;
                }

                case 0x00EE: {

                    unsigned char pc_1 = bus->read(++SP);
                    unsigned char pc_2 = bus->read(++SP);

                    PC = pc_1 << 8 | pc_2;

                    break;
                }

            }

            inc();
            break;

        }

        case 0x1000: {
            PC = opcode & 0x0FFF;
            break;
        }

        case 0x2000: {

            unsigned char pc_1 = (PC >> 8) & 0xFF;
            unsigned char pc_2 = PC & 0xFF;


            bus->write(SP--, pc_2);
            bus->write(SP--, pc_1);


            PC = opcode & 0x0FFF;


            break;

        }

        case 0x3000: {


            //Skips the next instruction if VX equals NN (usually the next instruction is a jump to skip a code block).

            unsigned char reg = (opcode >> 8) & 0x0F;
            unsigned char value = opcode & 0xFF;

            if (registers[reg] == value) {
                skip();
            } else {
                inc();
            }

            break;
        }

        case 0x4000: {


            //Skips the next instruction if VX does not equal NN (usually the next instruction is a jump to skip a code block).

            unsigned char reg = (opcode >> 8) & 0x0F;
            unsigned char value = opcode & 0xFF;

            if (registers[reg] != value) {
                skip();
            } else {
                inc();
            }


            break;

        }

        case 0x5000: {



            //Skips the next instruction if VX equals VY (usually the next instruction is a jump to skip a code block).
            unsigned char reg_1 = (opcode >> 8) & 0x0F;
            unsigned char reg_2 = (opcode >> 4) & 0x0F;

            if (registers[reg_1] == registers[reg_2]) {
                skip();
            } else {
                inc();
            }

            break;

        }

        case 0x6000: {




            //Sets VX to NN.
            unsigned char reg = (opcode >> 8) & 0x0F;
            unsigned char value = opcode & 0xFF;

            registers[reg] = value;
            inc();
            break;

        }

        case 0x7000: {



            //Adds NN to VX (carry flag is not changed).
            unsigned char reg = (opcode >> 8) & 0x0F;
            unsigned char value = opcode & 0xFF;

            registers[reg] += value;
            inc();
            break;

        }

        case 0x8000: {


            unsigned char reg_1 = (opcode >> 8) & 0x0F;
            unsigned char reg_2 = (opcode >> 4) & 0x0F;
            unsigned char value_1 = registers[reg_1];
            unsigned char value_2 = registers[reg_2];

            switch (opcode & 0x000F) {

                case 0x0000: {

                    //Sets VX to the value of VY.
                    registers[reg_1] = value_2;
                    inc();
                    break;
                }
                case 0x0001: {

                    //Sets VX to VX or VY. (bitwise OR operation).


                    registers[reg_1] |= value_2;
                    inc();
                    break;
                }
                case 0x0002: {

                    //Sets VX to VX and VY. (bitwise AND operation).


                    registers[reg_1] &= value_2;
                    inc();

                    break;
                }
                case 0x0003: {

                    //Sets VX to VX xor VY.
                    registers[reg_1] ^= value_2;

                    inc();

                    break;
                }

                case 0x0004: {

                    unsigned short sum = value_1 + value_2;

                    if (sum > 0xFF) {
                        registers[0x0F] = 1;
                        registers[reg_1] = sum & 0xFF;
                    } else {
                        registers[0x0F] = 0;
                        registers[reg_1] = sum;
                    }

                    inc();

                    break;
                }

                case 0x0005: {

                    if (value_1 >= value_2) {
                        registers[0x0F] = 1;
                    } else {
                        registers[0x0F] = 0;
                    }

                    registers[reg_1] -= value_2;

                    inc();

                    break;
                }
                case 0x0006: {

                    registers[0x0F] = value_1 & 0x0F;
                    registers[reg_1] >>= 1;

                    inc();

                    break;
                }
                case 0x0007: {

                    if (value_2 >= value_1) {
                        registers[0x0F] = 1;
                    } else {
                        registers[0x0F] = 0;
                    }

                    registers[reg_1] = value_2 - value_1;

                    inc();

                    break;
                }
                case 0x000E: {

                    //Shifts VX to the left by 1, then sets VF to 1 if the most significant bit of VX prior to that shift was set, or to 0 if it was unset.
                    registers[0x0F] = (value_1 & 0x80) ? 1 : 0;
                    registers[reg_1] <<= 1;

                    inc();

                    break;
                }

            }

            break;
        }

        case 0x9000: {



            //Skips the next instruction if VX does not equal VY. (Usually the next instruction is a jump to skip a code block).

            unsigned char reg_1 = (opcode >> 8) & 0x0F;
            unsigned char reg_2 = (opcode >> 4) & 0x0F;

            if (registers[reg_1] != registers[reg_2]) {
                skip();
            } else {
                inc();
            }

            break;

        }

        case 0xA000: {



            //Sets I to the address NNN.

            I = opcode & 0x0FFF;
            inc();

            break;

        }

        case 0xB000: {


            //Jumps to the address NNN plus V0.

            PC = opcode & 0xF000;
            PC += registers[0];

            break;

        }

        case 0xC000: {



            //Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.

            srand(time(0)); // seed the random number generator
            unsigned char random_number = rand() % 256; // generate a random number between 0 and 255

            unsigned char reg = (opcode >> 8) & 0x000F;
            unsigned char value = opcode & 0xFF;

            registers[reg] = random_number & value;

            inc();

            break;
        }

        case 0xD000: {


            unsigned char x = registers[(opcode >> 8) & 0x0F];
            unsigned char y = registers[(opcode >> 4) & 0x0F];
            unsigned char height = opcode & 0x000F;

            registers[0x0F] = 0;

            for (int cur_height = 0; cur_height < height; cur_height++) {


                unsigned char sprite_row = bus->read(I + cur_height);

                for (unsigned char bit_shift = 0; bit_shift < 8; bit_shift++) {

                    unsigned char cur_bit = sprite_row & (0x80 >> bit_shift);
                    cur_bit = cur_bit != 0 ? 0x01 : 0x00;
                    if (cur_bit != 0) {
                        if (graphics->at(x, y) == 1) registers[0x0F] = 1;
                        unsigned char position_x = x + bit_shift;
                        unsigned char position_y = y + cur_height;
                        graphics->set(position_y, position_x, cur_bit);
                    }
                }


            }

            inc();

            break;
        }

        case 0xE000: {

            unsigned char reg = (opcode >> 8) & 0x0F;
            unsigned char key_number = registers[reg];

            switch (opcode & 0x00FF) {


                case 0x009E: {

                    if (input->get_key(key_number)) {
                        skip();
                    } else {
                        inc();
                    }


                    break;
                }

                case 0x00A1: {

                    if (!input->get_key(key_number)) {
                        skip();
                    } else {
                        inc();
                    }

                    break;
                }

                default:
                    throw "Unknown opcode " + opcode;


            }

            break;

        }

        case 0xF000: {


            unsigned char reg = (opcode >> 8) & 0x0F;
            unsigned char reg_value = registers[reg];

            switch (opcode & 0x00FF) {

                case 0x0007: {

                    registers[reg] = DT;
                    inc();

                    break;
                }

                case 0x000A: {
                    //TODO implement the delay timer to halt the emulator
                    //A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event).
                    for (int i = 0; i < 16; i++) {
                        if (input->get_key(i)) {
                            inc();

                            break;
                        }
                    }


                    break;
                }

                case 0x0015: {

                    DT = reg_value;
                    inc();

                    break;
                }

                case 0x0018: {
                    ST = reg_value;
                    inc();

                    break;
                }

                case 0x001E: {

                    I += reg_value;
                    inc();

                    break;
                }

                case 0x0029: {
                    //Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
                    //TODO implement
                    inc();
                    break;
                }

                case 0x0033: {

                    bus->write(I, registers[(opcode & 0x0F00) >> 8] / 100);
                    bus->write(I + 1, (registers[(opcode & 0x0F00) >> 8] / 10) % 10);
                    bus->write(I + 2, (registers[(opcode & 0x0F00) >> 8] % 100) % 10);

                    inc();

                    break;
                }
                case 0x0055: {
                    for (unsigned char it = 0; it <= reg; it++) {
                        bus->write(I + it, registers[it]);
                    }

                    inc();

                    break;
                }

                case 0x0065: {

                    for (unsigned char it = 0; it <= reg; it++) {
                        registers[it] = bus->read(I + it);
                    }

                    inc();

                    break;

                }

                default:
                    throw "Unknown opcode " + opcode;


            }


            break;

        }

        default: {
            throw "Unknown opcode " + opcode;
        }
    }

}

void CPU::skip() {
    PC += 4;
}

void CPU::inc() {
    PC += 2;
}
