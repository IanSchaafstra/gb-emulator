#include <iostream>

#include "cpu.h"
#include "register_bindings.h"

void CPU::POP_R16(uint8_t instruction) {

    uint8_t lower = _sp;
    _sp++;
    uint8_t upper = _sp;
    _sp++;

    switch (instruction) {
        case 0xC1:
            _registers[B] = upper;
            _registers[C] = lower;
            break;
        case 0xD1:
            _registers[D] = upper;
            _registers[E] = lower;
            break;
        case 0xE1:
            _registers[H] = upper;
            _registers[L] = lower;
            break;
        case 0xF1:
            _registers[A] = upper;
            _registers[F] = lower;
            break;
        default:
            std::cerr << "Invalid POP function! Attempted to POP with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    _pc += 3;
}

void CPU::PUSH_RP(uint8_t instruction) {
    uint8_t first;
    uint8_t second;

    switch (instruction) {
        case 0xC5:
            first = _registers[B];
            second = _registers[C];
            break;
        case 0xD5:
            first = _registers[D];
            second = _registers[E];
            break;
        case 0xE5:
            first = _registers[H];
            second = _registers[L];
            break;
        case 0xF5:
            first = _registers[A];
            second = _registers[F];
            break;
        default:
            std::cerr << "Invalid PUSH function! Attempted to PUSH_RP with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _sp--;
    _memory[_sp] = first;
    _sp--;
    _memory[_sp] = second;

    _pc++;
}
