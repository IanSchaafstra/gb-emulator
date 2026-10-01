#pragma once
#include <cstdint>
#include "registers.h"

class Gameboy {
    Gameboy() = default;
private:
    uint8_t _ram[8192];
    uint8_t _vram[8192];

    bool _screen[144][160]; // just a bool for now, will change it to something more sophisticated at some point
    Registers _registers;
};
