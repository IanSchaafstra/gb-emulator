#include "cpu.h"

#include <iostream>

void CPU::ADD_HL_R16(uint8_t instruction) {
    uint16_t value;
    switch (instruction) {
        case 0x09:
            value = getBC();
            break;
        case 0x19:
            value = getDE();
            break;
        case 0x29:
            value = getHL();
            break;
        case 0x39:
            value = _sp;
            break;
        default:
            std::cerr << "Invalid ADD function! Attempted to ADD with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    bool bit15Value = (value >> 15) & 1;
    bool bit15HL = (getHL() >> 15) & 1;

    bool bit11Value = (value >> 11) & 1;
    bool bit11HL = (getHL() >> 11) & 1;

    uint16_t result = value + getHL();

    setHL(result);

    setNFlag(false);

    if (((result >> 15) & 1) == 1) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }

    if (((result >> 11) & 1) == 1) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    _pc++;
}
