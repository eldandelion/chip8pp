//
// Created by Daniel on 2024/8/23.
//

#ifndef CHIP8PP_BUS_H
#define CHIP8PP_BUS_H

#include "RAM.h"


class BUS {

private:
     RAM *ram;

public:

    explicit BUS(RAM *ram);

    unsigned char read(unsigned const short &address);

    void write(unsigned const short &address, unsigned const char &value);

};


#endif //CHIP8PP_BUS_H
