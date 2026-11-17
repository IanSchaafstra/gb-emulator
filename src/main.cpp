#include <cstdint>
#include <iostream>

#include <fstream>
#include <iomanip>
#include <vector>

#include "gameboy.h"

int main() {
    std::ifstream inputFile("resources/Tetris (World) (Rev 1).gb", std::ios::in | std::ios::binary);
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    Gameboy gb;

    // for (auto c : buffer) {
    //     std::cout << std::hex << std::setw(2) << static_cast<unsigned short>(c) << std::endl;
    // }
    gb.loadRom(buffer);

    // std::cout << std::hex << gb.getCharAtRomIndex(gb.getProgramCounter() + 1) << std::endl;
    while (true) {
        gb.fetchInstruction();
    }
    return 0;
}
