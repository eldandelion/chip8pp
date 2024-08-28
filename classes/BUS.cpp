//
// Created by Daniel on 2024/8/23.
//

#include "../headers/BUS.h"

BUS::BUS( RAM *ram) : ram(ram) {}

unsigned char BUS::read(const unsigned short &address) {
    return ram->read(address);
}

void BUS::write(const unsigned short &address, const unsigned char &value) {
    ram->write(address, value);
}


