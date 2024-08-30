#include <iostream>


#include "RAM.h"
#include "Game.h"
#include "CPU.h"
#include "Input.h"
#include <thread>

constexpr unsigned char fontset[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

constexpr unsigned short FONT_ADDRESS = 0x50;
constexpr Uint32 TARGET_FPS = 500;
const Uint32 FRAME_DURATION = 1000 / TARGET_FPS;

int main() {


    auto *game = new Game();
    auto *ram = new RAM();
    auto *bus = new BUS(ram);
    auto *graphics = new Graphics();
    auto *input = new Input();
    auto *cpu = new CPU(bus, graphics, input);


    unsigned short address = FONT_ADDRESS;

    for (unsigned char byte: fontset) {
        bus->write(address++, byte);
    }

    //game->load("/Volumes/Files/Programming/chip8pp/resources/ibm-logo.ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/6-keypad.ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/3-corax+.ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/4-flags.ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/5-quirks.ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/2048 (by Dr Gergo Erdi)(2014).ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/Blitz (fix) (by David Winter).ch8", bus);
    game->load("/Volumes/Files/Programming/chip8pp/resources/Pong (1 player).ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/Tetris (by 12me21)(2017).ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/Spooky Spot [Joseph Weisbecker, 1978].ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/15 Puzzle (by Roger Ivie)(19xx).ch8", bus);
    //game->load("/Volumes/Files/Programming/chip8pp/resources/Airplane (unknown)(19xx).ch8", bus);


    graphics->init();
    cpu->init();

    Uint32 last_render_time = SDL_GetTicks();


    bool running = true;
    while (running) {

        Uint32 current_time = SDL_GetTicks();
        Uint32 delta_time = current_time - last_render_time;

        cpu->fetch_opcode();
        cpu->timers_tick();
        graphics->render();
        input->monitor_keypress(graphics->get_event());


        // Calculate remaining time to maintain 500 Hz
        if (delta_time < FRAME_DURATION) {
            SDL_Delay(FRAME_DURATION - delta_time);
        }

        last_render_time = current_time;
    }


    return 0;
}






