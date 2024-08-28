//
// Created by Daniel on 2024/8/23.
//

#include <sstream>
#include "../headers/RAM.h"
#include "iostream"

using std::ostringstream, std::runtime_error;

void RAM::clear() {

    for (unsigned char & it : memory) {
        it = 0x00;
    }

}

unsigned char RAM::read(unsigned const short &address) {

    range_check(address);
    return memory[address];
}

void RAM::write(const unsigned short &address, const unsigned char &value) {
    range_check(address);

    memory[address] = value;
}

bool RAM::range_check(const unsigned short &address) {

    if (address > 4096u) {
        std::ostringstream oss;
        oss << "unacceptable memory address " << address;
        throw std::runtime_error(oss.str());
    }
    return true;
}
