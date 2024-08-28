//
// Created by Daniel on 2024/8/23.
//

#ifndef CHIP8PP_RAM_H
#define CHIP8PP_RAM_H

class RAM {

private:

    unsigned char memory[4096];


public:

    void clear();

    unsigned char read(unsigned const short &address);

    void write(unsigned const short &address, const unsigned char &value);

    static bool range_check(const unsigned short &address);



};


#endif //CHIP8PP_RAM_H
