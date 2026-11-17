#include "cpu.h"

#include <iostream>

void CPU::JR(int8_t a) {
    _pc += a;
}

void CPU::JR_CONDITIONAL(uint8_t instruction, int8_t value) {
    bool should_jump = false;
    switch (instruction) {
        case 0x20:
            should_jump = getZFlag() == false;
            break;
        case 0x30:
            should_jump = getCFlag() == false;
            break;
        case 0x28:
            should_jump = getZFlag() == true;
            break;
        case 0x38:
            should_jump = getCFlag() == true;
            break;
        default:
            std::cerr << "Invalid conditional JR! Attempted to JR_CONDITIONAL with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _pc += 2;
    if (should_jump) {
        JR(value);
    }
}

void CPU::JP(uint16_t address) {
    _pc = address;
}

void CPU::JP_CONDITIONAL(uint8_t instruction, uint16_t address) {
    bool should_jump = false;
    switch (instruction) {
        case 0xC2:
            if (getZFlag() == false) {
                should_jump = true;
            }
            break;
        case 0xD2:
            if (getCFlag() == false) {
                should_jump = true;
            }
            break;
        case 0xCA:
            if (getZFlag()) {
                should_jump = true;
            }
            break;
        case 0xDA:
            if (getCFlag()) {
                should_jump = true;
            }
            break;

        default:
            std::cerr << "Invalid conditional JP! Attempted to JP_CONDITIONAL with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    if (should_jump) {
        _pc = address;
    } else {
        _pc += 3;
    }
}

void CPU::CALL(uint8_t instruction, uint16_t address) {
    bool shouldCall = false;

    switch (instruction) {
        case 0xCC:
            if (getZFlag() == true) {
                shouldCall = true;
            }
            break;
        case 0xCD:
            shouldCall = true;
            break;
        case 0xDC:
            if (getCFlag() == false) {
                shouldCall = true;
            }
            break;
        default:
            std::cerr << "Invalid CALL! Attempted to CALL with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    if (shouldCall == true) {
        _sp--;
        _memory[_sp] = _memory[_pc + 3];
        _sp--;
        _memory[_sp] = _memory[_pc + 4];

        JP(address);
    } else {
        _pc += 3;
    }
}

void CPU::RET(uint8_t instruction) {
    bool shouldRet = false;
    switch (instruction) {
        case 0xC0:
            if (getZFlag() == false) {
                shouldRet = true;
            }
            break;
        case 0xD0:
            if (getCFlag() == false) {
                shouldRet = true;
            }
            break;
        case 0xC8:
            if (getZFlag() == true) {
                shouldRet = true;
            }
            break;
        case 0xD8:
            if (getCFlag() == true) {
                shouldRet = true;
            }
            break;
        case 0xC9:
            shouldRet = true;
            break;
        default:
            std::cerr << "Invalid RET! Attempted to RET with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    if (shouldRet) {
        uint8_t lower = _memory[_sp];
        _sp++;
        uint8_t upper = _memory[_sp];
        _sp++;

        uint16_t address = (upper << 8) | lower;

        _pc = address;
    } else {
        _pc++;
    }
}

void CPU::RST(uint8_t instruction) {
    uint8_t address;
    switch (instruction) {
        case 0xC7:
            address = 0x00;
            break;
        case 0xCF:
            address = 0x08;
            break;
        case 0xD7:
            address = 0x10;
            break;
        case 0xDF:
            address = 0x18;
            break;
        case 0xE7:
            address = 0x20;
            break;
        case 0xEF:
            address = 0x28;
            break;
        case 0xF7:
            address = 0x30;
            break;
        // case 0xFF:
        //     address = 0x38;
        //     break;
        default:
            std::cerr << "Invalid RST! Attempted to RST with instruction: " << std::hex << static_cast<unsigned short>(instruction) << " which is not a valid instruction!" << std::endl;
            std::exit(2);
            return;
    }

    uint16_t returnAddr = _pc + 1;

    Twobytes currPC{_pc};

    _sp--;
    _memory[_sp] = currPC.second;
    _sp--;
    _memory[_sp] = currPC.first;

    _pc = address;
}
