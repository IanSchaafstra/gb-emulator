#include "cpu.h"

#include "register_bindings.h"

void CPU::setZFlag(bool state) {
    uint8_t mask = 1 << 7;

    if (state == true) {
        _registers[1] |= mask;
    } else {
        _registers[1] &= ~mask;
    }
}

void CPU::setNFlag(bool state) {
    uint8_t mask = 1 << 6;

    if (state == true) {
        _registers[1] |= mask;
    } else {
        _registers[1] &= ~mask;
    }
}
void CPU::setHFlag(bool state) {
    uint8_t mask = 1 << 5;

    if (state == true) {
        _registers[1] |= mask;
    } else {
        _registers[1] &= ~mask;
    }
}

void CPU::setCFlag(bool state) {
    uint8_t mask = 1 << 4;

    if (state == true) {
        _registers[1] |= mask;
    } else {
        _registers[1] &= ~mask;
    }
}

bool CPU::getZFlag() {
    return (_registers[1] >> 7) & static_cast<uint8_t>(1);
}

bool CPU::getNFlag() {
    return (_registers[1] >> 6) & static_cast<uint8_t>(1);
}

bool CPU::getHFlag() {
    return (_registers[1] >> 5) & static_cast<uint8_t>(1);
}

bool CPU::getCFlag() {
    return (_registers[1] >> 4) & static_cast<uint8_t>(1);
}

uint16_t CPU::getAF() {
    uint16_t returnVal = _registers[F] << 8;
    returnVal |= _registers[A];

    return returnVal;
}

uint16_t CPU::getBC() {
    uint16_t returnVal = _registers[C] << 8;
    returnVal |= _registers[B];

    return returnVal;
}

uint16_t CPU::getDE() {
    uint16_t returnVal = _registers[E] << 8;
    returnVal |= _registers[D];

    return returnVal;
}

uint16_t CPU::getHL() {
    uint16_t returnVal = _registers[L] << 8;
    returnVal |= _registers[H];

    return returnVal;
}

void CPU::setAF(uint16_t value) {
    uint8_t a = value & 0xFF;
    uint8_t f = value >> 8 & 0xFF;

    _registers[A] = a;
    _registers[F] = f;
}

void CPU::setBC(uint16_t value) {
    uint8_t b = value & 0xFF;
    uint8_t c = value >> 8 & 0xFF;

    _registers[B] = b;
    _registers[C] = c;
}

void CPU::setDE(uint16_t value) {
    uint8_t d = value & 0xFF;
    uint8_t e = value >> 8 & 0xFF;

    _registers[D] = d;
    _registers[E] = e;
}

void CPU::setHL(uint16_t value) {
    uint8_t h = value & 0xFF;
    uint8_t l = value >> 8 & 0xFF;

    _registers[H] = l;
    _registers[L] = h;
}
