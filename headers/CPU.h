//
// Created by Daniel on 2024/8/23.
//

#ifndef CHIP8PP_CPU_H
#define CHIP8PP_CPU_H


#include "BUS.h"
#include "Graphics.h"
#include "Input.h"

class CPU {

private:


    BUS *bus;
    Graphics *graphics;
    Input *input;

    unsigned char registers[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    unsigned short PC = 0x0000;
    unsigned short SP = 0x0000;
    unsigned short I = 0x0000;

    unsigned char DT = 0x00; //delay timer
    unsigned char ST = 0x00; //sound timer

    unsigned short opcode = 0x0000;

    unsigned char cycle_count = 12;

    void decode_opcode();

    void skip();
    void inc();

public:

    explicit CPU(BUS *bus, Graphics *graphics, Input *input);


    void init();

    void timers_tick();


    void fetch_opcode();
};


#endif //CHIP8PP_CPU_H
