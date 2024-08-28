//
// Created by Daniel on 2024/8/26.
//

#include "Input.h"
#include <ncurses.h>
#include "SDL.h"

void Input::monitor_keypress(SDL_Event &event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    keys[1] = true;
                    break;
                case SDLK_2:
                    keys[2] = true;
                    break;
                case SDLK_3:
                    keys[3] = true;
                    break;
                case SDLK_4:
                    keys[12] = true;

                    break;
                case SDLK_q:
                    keys[4] = true;

                    break;
                case SDLK_w:
                    keys[5] = true;

                    break;
                case SDLK_e:
                    keys[6] = true;

                    break;
                case SDLK_r:
                    keys[13] = true;

                    break;
                case SDLK_a:
                    keys[7] = true;

                    break;
                case SDLK_s:
                    keys[8] = true;

                    break;
                case SDLK_d:
                    keys[9] = true;

                    break;
                case SDLK_f:
                    keys[14] = true;

                    break;
                case SDLK_z:
                    keys[10] = true;

                    break;
                case SDLK_x:
                    keys[0] = true;

                    break;
                case SDLK_c:
                    keys[11] = true;

                    break;
                case SDLK_v:
                    keys[15] = true;

                    break;
                default:
                    printf("Unknown key press: %c\n", event.key.keysym.sym);
                    break;
            }


        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    keys[1] = false;

                    break;
                case SDLK_2:
                    keys[2] = false;
                    break;
                case SDLK_3:
                    keys[3] = false;
                    break;
                case SDLK_4:
                    keys[12] = false;

                    break;
                case SDLK_q:
                    keys[4] = false;

                    break;
                case SDLK_w:
                    keys[5] = false;

                    break;
                case SDLK_e:
                    keys[6] = false;

                    break;
                case SDLK_r:
                    keys[13] = false;

                    break;
                case SDLK_a:
                    keys[7] = false;

                    break;
                case SDLK_s:
                    keys[8] = false;

                    break;
                case SDLK_d:
                    keys[9] = false;

                    break;
                case SDLK_f:
                    keys[14] = false;

                    break;
                case SDLK_z:
                    keys[10] = false;

                    break;
                case SDLK_x:
                    keys[0] = false;

                    break;
                case SDLK_c:
                    keys[11] = false;

                    break;
                case SDLK_v:
                    keys[15] = false;

                    break;
                default:
                    printf("Unknown key press: %c\n", event.key.keysym.sym);
                    break;
            }
        }
    }

}

const bool *Input::get_keys() const {
    return keys;
}



const bool Input::get_key(unsigned char number) const {
    return keys[number];
}

Input::Input() {


    for (int it = 0; it < 16; it++) {
        keys[it] = false;
    }
}
