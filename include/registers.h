#pragma once
#include <cstdint>

class Registers {
private:
    uint8_t _regA = 0;
    uint8_t _regB = 0;
    uint8_t _regC = 0;
    uint8_t _regD = 0;
    uint8_t _regE = 0;
    uint8_t _regH = 0;
    uint8_t _regL = 0;

    uint16_t _sp = 0;
    uint16_t _pc = 0;
};
