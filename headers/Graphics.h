//
// Created by Daniel on 2024/8/26.
//

#ifndef CHIP8PP_GRAPHICS_H
#define CHIP8PP_GRAPHICS_H
#include "SDL.h"
#include <map>


class Graphics {

private:

    SDL_Event event;

    SDL_Renderer* renderer;

    SDL_Texture *frameBufferTexture;

    SDL_Rect dest_rect;

    SDL_Window* window;

    SDL_Surface *frameBuffer = SDL_CreateRGBSurface(0, 640, 320, 32, 0, 0, 0, 0);

    unsigned char gfx[32][64];


public:

    void clear();

    void set(unsigned char &x, unsigned char &y);

    void update();

    unsigned char at(unsigned char &x, unsigned char &y) const;

    void init();

    void render();

    SDL_Event& get_event();


};


#endif //CHIP8PP_GRAPHICS_H
