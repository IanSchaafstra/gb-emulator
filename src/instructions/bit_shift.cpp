#include "cpu.h"
#include "register_bindings.h"

void CPU::RRA() {
    auto a = _registers[A];

    bool setC = a & 1;

    uint8_t mask = 1 << 7;

    a = a >> 1;

    if (getCFlag()) {
        a = a | mask;
    }

    _registers[A] = a;

    if (setC) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }
    setZFlag(false);
    setNFlag(false);
    setHFlag(false);

    _pc++;
}

void CPU::RRCA() {
    auto a = _registers[A];

    bool firstBit = a & 1;

    uint8_t mask = 1 << 7;

    a = a >> 1;

    if (firstBit) {
        a = a | mask;
    }

    _registers[A] = a;

    if (firstBit) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }
    setZFlag(false);
    setNFlag(false);
    setHFlag(false);

    _pc++;
}

void CPU::RLCA() {
    bool bit7A = (_registers[A] >> 7) & 1;

    _registers[A] <<= 1;

    if (bit7A) {
        _registers[A] = _registers[A] | 1;
        setCFlag(true);
    } else {
        _registers[A] = _registers[A] & ~1;
        setCFlag(false);
    }
    setZFlag(false);
    setNFlag(false);
    setHFlag(false);

    _pc++;
}
