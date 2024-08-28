//
// Created by Daniel on 2024/8/23.
//

#include <fstream>
#include "Game.h"

#include "iostream"

using std::cout;

std::vector<uint8_t> *Game::load(char *filepath, BUS *bus) {


    snprintf(filename, sizeof(filename), "%s", filepath);
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open() || !file.good()) {
        printf("Failed to open file: %s", filename);
        return {};
    }


    file_data->assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    std::string title_string(file_data->begin(), file_data->begin() + 8);


    printf("\ntitle %s", title_string.c_str());

    std::copy(file_data->begin() + offset, file_data->end(), std::back_inserter(*content));

    unsigned short address = STARTING_ADDRESS;

    for (unsigned char byte: *content) {
        bus->write(address++, byte);
    }

    return file_data;
}

Game::Game() : file_data(new std::vector<uint8_t>()), content(new std::vector<unsigned char>()) {}
