#pragma once
#include <cstdint>
#include <vector>

#include "cpu.h"
#include "twobytes.h"


class Gameboy {
public:
    Gameboy() = default;
    void fetchInstruction(); // gets the instruction at the program counter and calls the corresponding function
    void loadRom(std::vector<uint8_t> &rom);
    int instructionCount = 0;
private:
    CPU _cpu;

    bool _screen[144][160]; // just a bool for now, will change it to something more sophisticated at some point
};
