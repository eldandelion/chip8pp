cmake_minimum_required(VERSION 3.25)
project(chip8pp)

set(CMAKE_CXX_STANDARD 23)

add_executable(chip8pp main.cpp headers/RAM.h classes/RAM.cpp headers/BUS.h classes/BUS.cpp headers/Game.h classes/Game.cpp headers/Emu.h headers/CPU.h classes/CPU.cpp headers/Graphics.h classes/Graphics.cpp classes/Emu.cpp headers/Input.h classes/Input.cpp)

include_directories(
        "headers"
        "classes"
        "resources"
)


find_package(SDL2 REQUIRED COMPONENTS SDL2)
target_link_libraries(chip8pp PRIVATE SDL2::SDL2 ${CMAKE_DL_LIBS} -lncurses)
