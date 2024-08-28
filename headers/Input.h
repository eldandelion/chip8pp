//
// Created by Daniel on 2024/8/26.
//

#ifndef CHIP8PP_INPUT_H
#define CHIP8PP_INPUT_H


#include <SDL.h>

class Input {

private:

    bool keys[16];


public:
    void monitor_keypress(SDL_Event &event);

    const bool *get_keys() const;

    const bool get_key(unsigned char number) const;

    Input();

};


#endif //CHIP8PP_INPUT_H
