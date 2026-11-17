#include "gameboy.h"

#include <iomanip>
#include <iostream>
#include <thread>


void Gameboy::loadRom(std::vector<uint8_t> &rom) {
    _cpu.loadRom(rom);
}

void Gameboy::fetchInstruction() {
    _cpu.fetchInstruction();
}
