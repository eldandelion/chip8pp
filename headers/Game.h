//
// Created by Daniel on 2024/8/23.
//

#ifndef CHIP8PP_GAME_H
#define CHIP8PP_GAME_H

#include "vector"
#include "string"
#include "BUS.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>


class Game {

private:

    static constexpr unsigned short STARTING_ADDRESS = 0x0200;

    std::vector<unsigned char> *file_data;

    int size;

    char filename[1024]{};

    std::string title;

    char *author;

    std::vector<unsigned char> *content;

    const int offset = 0;


public:

    explicit Game();

    std::vector<uint8_t> *load(char *filepath, BUS *bus);


};


#endif //CHIP8PP_GAME_H
