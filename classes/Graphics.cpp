//
// Created by Daniel on 2024/8/26.
//

#include "Graphics.h"

void Graphics::clear() {

    // Fill the rendering surface with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Clear the frame buffer
    Uint32 *pixels = (Uint32 *)frameBuffer->pixels;
    for (int i = 0; i < 640 * 320; i++) {
        pixels[i] = 0x00000000; // Black pixel
    }

    // Clear the gfx array
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 64; j++) {
            gfx[i][j] = 0x00;
        }
    }

    // Update the texture
    SDL_Texture *frameBufferTexture = SDL_CreateTextureFromSurface(renderer, frameBuffer);
    SDL_RenderCopy(renderer, frameBufferTexture, nullptr, &dest_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(frameBufferTexture);

}

void Graphics::set(unsigned char &x, unsigned char &y, unsigned char value) {

    gfx[x][y] ^= value;

    // Render the pixel to the frame buffer
    Uint32 *pixels = (Uint32 *) frameBuffer->pixels;
    pixels[y + x * 640] = gfx[x][y] == 0 ? 0x00000000 : 0xFFFFFFFF; // Goes black if bit set to 0, otherwise sets white pixel


    SDL_Texture *frameBufferTexture = SDL_CreateTextureFromSurface(renderer, frameBuffer);

    SDL_RenderCopy(renderer, frameBufferTexture, nullptr, &dest_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(frameBufferTexture);

}


unsigned char Graphics::at(unsigned char &x, unsigned char &y) const {
    return gfx[x][y];
}

void Graphics::init() {


    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window with a rendering surface
    if (SDL_CreateWindowAndRenderer(640, 320, 0, &window, &renderer) < 0) {
        printf("Error creating window and renderer: %s\n", SDL_GetError());

    }

    SDL_RenderSetScale(renderer, 10, 10);

    clear();

    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = 640; // e.g., 640
    dest_rect.h = 320; // e.g., 320


}

void Graphics::render() {
    // Present the rendering surface to the screen

}

SDL_Event& Graphics::get_event() {
    return event;
}


