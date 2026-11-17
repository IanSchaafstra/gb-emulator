#include "cpu.h"
#include "register_bindings.h"

#include <iostream>

void CPU::LD_HLD_A() {
    _memory[getHL()] = _registers[A];
    setHL(getHL() - 1);
    _pc++;
}

void CPU::LD(uint8_t instruction, uint8_t val) {
    switch (instruction) {
        case 0x06:
            _registers[B] = val;
            break;
        case 0x0E:
            _registers[C] = val;
            break;
        case 0x16:
            _registers[D] = val;
            break;
        case 0x1E:
            _registers[E] = val;
            break;
        case 0x26:
            _registers[H] = val;
            break;
        case 0x2E:
            _registers[L] = val;
            break;
        case 0x3E:
            _registers[A] = val;
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    _pc += 2;
}

void CPU::LD_B(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x40:
            value = _registers[B];
            break;
        case 0x41:
            value = _registers[C];
            break;
        case 0x42:
            value = _registers[D];
            break;
        case 0x43:
            value = _registers[E];
            break;
        case 0x44:
            value = _registers[H];
            break;
        case 0x45:
            value = _registers[L];
            break;
        case 0x46:
            value = _memory[getHL()];
            break;
        case 0x47:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register B with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[B] = value;
    _pc++;
}

void CPU::LD_C(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x48:
            value = _registers[B];
            break;
        case 0x49:
            value = _registers[C];
            break;
        case 0x4A:
            value = _registers[D];
            break;
        case 0x4B:
            value = _registers[E];
            break;
        case 0x4C:
            value = _registers[H];
            break;
        case 0x4D:
            value = _registers[L];
            break;
        case 0x4E:
            value = _memory[getHL()];
            break;
        case 0x4F:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register C with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[C] = value;
    _pc++;
}

void CPU::LD_D(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x50:
            value = _registers[B];
            break;
        case 0x51:
            value = _registers[C];
            break;
        case 0x52:
            value = _registers[D];
            break;
        case 0x53:
            value = _registers[E];
            break;
        case 0x54:
            value = _registers[H];
            break;
        case 0x55:
            value = _registers[L];
            break;
        case 0x56:
            value = _memory[getHL()];
            break;
        case 0x57:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register D with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[D] = value;
    _pc++;
}

void CPU::LD_E(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x58:
            value = _registers[B];
            break;
        case 0x59:
            value = _registers[C];
            break;
        case 0x5A:
            value = _registers[D];
            break;
        case 0x5B:
            value = _registers[E];
            break;
        case 0x5C:
            value = _registers[H];
            break;
        case 0x5D:
            value = _registers[L];
            break;
        case 0x5E:
            value = _memory[getHL()];
            break;
        case 0x5F:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register C with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[E] = value;
    _pc++;
}

void CPU::LD_H(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x60:
            value = _registers[B];
            break;
        case 0x61:
            value = _registers[C];
            break;
        case 0x62:
            value = _registers[D];
            break;
        case 0x63:
            value = _registers[E];
            break;
        case 0x64:
            value = _registers[H];
            break;
        case 0x65:
            value = _registers[L];
            break;
        case 0x66:
            value = _memory[getHL()];
            break;
        case 0x67:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register D with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[H] = value;
    _pc++;
}

void CPU::LD_L(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x68:
            value = _registers[B];
            break;
        case 0x69:
            value = _registers[C];
            break;
        case 0x6A:
            value = _registers[D];
            break;
        case 0x6B:
            value = _registers[E];
            break;
        case 0x6C:
            value = _registers[H];
            break;
        case 0x6D:
            value = _registers[L];
            break;
        case 0x6E:
            value = _memory[getHL()];
            break;
        case 0x6F:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register C with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[L] = value;
    _pc++;
}

void CPU::LD_A(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x78:
            value = _registers[B];
            break;
        case 0x79:
            value = _registers[C];
            break;
        case 0x7A:
            value = _registers[D];
            break;
        case 0x7B:
            value = _registers[E];
            break;
        case 0x7C:
            value = _registers[H];
            break;
        case 0x7D:
            value = _registers[L];
            break;
        case 0x7E:
            value = _memory[getHL()];
            break;
        case 0x7F:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into register C with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[A] = value;
    _pc++;
}

void CPU::LD_HL_R8(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x70:
            value = _registers[B];
            break;
        case 0x71:
            value = _registers[C];
            break;
        case 0x72:
            value = _registers[D];
            break;
        case 0x73:
            value = _registers[E];
            break;
        case 0x74:
            value = _registers[H];
            break;
        case 0x75:
            value = _registers[L];
            break;
        case 0x77:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into location of HL with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _memory[getHL()] = value;

    _pc++;
}

void CPU::LD_N16_SP(const uint16_t address) {
    _memory[address] = _sp & 0xFF;
    _memory[address + 1] = _sp >> 8;

    _pc += 3;
}

void CPU::LD_RP(uint8_t instruction, uint16_t value) {
    switch (instruction) {
        case 0x01:
            setBC(value);
            break;
        case 0x11:
            setDE(value);
            break;
        case 0x21:
            setHL(value);
            break;
        case 0x31:
            _sp = value;
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load into location of RP with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    _pc += 3;
}

void CPU::LD_RP_A(uint8_t instruction) {
    switch (instruction) {
        case 0x02:
            _memory[getBC()] = _registers[A];
            break;
        case 0x12:
            _memory[getDE()] = _registers[A];
            break;
        case 0x22:
            _memory[getHL()] = _registers[A];
            setHL(getHL() + 1);
            break;
        case 0x32:
            _memory[getHL()] = _registers[A];
            setHL(getHL() - 1);
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load A into location of RP with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    _pc++;
}

void CPU::LD_A_RP(uint8_t instruction) {
    switch (instruction) {
        case 0x0A:
            _registers[A] = _memory[getBC()];
            break;
        case 0x1A:
            _registers[A] = _memory[getDE()];
            break;
        case 0x2A:
            _registers[A] = _memory[getHL()];
            setHL(getHL() + 1);
            break;
        case 0x3A:
            _registers[A] = _memory[getHL()];
            setHL(getHL() - 1);
            break;
        default:
            std::cerr << "Invalid load function! Attempted to load location of RP into A with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    _pc++;
}

void CPU::LDH_A(uint8_t instruction, uint8_t address) {
    uint16_t fullAddress = 0xFF00 + address;
    std::cout << "LDH_A address: " << static_cast<unsigned short>(address) << std::endl;
    switch (instruction) {
        case 0xE0:
            _memory[fullAddress] = _registers[A];
            break;
        case 0xF0:
            _registers[A] = _memory[fullAddress];
            break;
        default:
            std::cerr << "Invalid load function! Attempted to LDH_A with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    _pc += 2;
}

void CPU::LD_SP_HL() {
    _sp = getHL();

    _pc++;
}
