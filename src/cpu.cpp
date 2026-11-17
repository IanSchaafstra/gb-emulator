#include "cpu.h"

#include <iomanip>
#include <iostream>

void CPU::loadRom(const std::vector<uint8_t> &rom) {
    if (rom.size() > 32786) {
        std::cerr << "Rom size is bigger than 32kb!" << std::endl;
        return;
    }

    for (int i = 0; i < rom.size(); i++) {
        _memory[i] = rom[i];
    }
}

void CPU::fetchInstruction() {
    auto instruction = _memory[_pc];
    auto a8 = _memory[_pc + 1];
    auto b8 = _memory[_pc + 2];
    uint16_t address = (b8 << 8) | a8;
    uint16_t a16 = (b8 << 8) | a8;
    Twobytes full{a8, b8};
    std::cout << "PC: " << std::hex << _pc << std::endl;
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned short>(_memory[_pc]) << std::endl;
    switch (_memory[_pc]) {
        case 0:
            _pc += 1;
            std::cout << "NOP" << std::endl;
            break;

        // jumps and subroutines
        case 0x18:
            JR(static_cast<int8_t>(a8));
            break;

        case 0x20: case 0x30: case 0x28: case 0x38:
            JR_CONDITIONAL(instruction, static_cast<int8_t>(a8));
            break;

        case 0xC3:
            JP(address);
            break;

        case 0xC2: case 0xD2: case 0xCA: case 0xDA:
            JP_CONDITIONAL(instruction, address);
            break;

        case 0xCC: case 0xCD: case 0xDC:
            CALL(instruction, address);
            break;

        case 0xC0: case 0xD0: case 0xC8: case 0xD8: case 0xC9:
            RET(instruction);
            break;

        case 0xC7: case 0xCF: case 0xD7: case 0xDF: case 0xE7: case 0xEF: case 0xF7: case 0xFF:
            RST(instruction);
            break;

        // 8-bit arithmetic and logic instructions
        case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA6: case 0xA7:
            AND_R(instruction);
            break;

        case 0xE6:
            AND_N(a8);
            break;

        case 0x05: case 0x0D: case 0x15: case 0x1D: case 0x25: case 0x2D: case 0x3D:
            DEC(instruction);
            break;

        case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C: case 0x3C:
            INC(instruction);
            break;

        case 0x03: case 0x13: case 0x23: case 0x33:
            INC_RP(instruction);
            break;

        case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: case 0x97:
            SUB_R(instruction);
            break;

        case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D: case 0x9E: case 0x9F:
            SBC_R(instruction);
            break;

        case 0xDE:
            SBC_N(a8);
            break;

        case 0xD6:
            SUB_N(a8);
            break;

        case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5:
            OR_R(instruction);
            break;

        case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD: case 0xBE: case 0xBF:
            CP_A_R(instruction);
            break;

        case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD: case 0xAE: case 0xAF:
            XOR_R(instruction);
            break;

        // 16-bit arithmetic instructions
        case 0x09: case 0x19: case 0x29: case 0x39:
            ADD_HL_R16(instruction);
            break;

        // bit shifting
        case 0x1F:
            RRA();
            break;

        case 0x0F:
            RRCA();
            break;

        case 0x07:
            RLCA();
            break;

        // load instructions
        case 0x06: case 0x0E: case 0x16: case 0x1E: case 0x26: case 0x2E: case 0x3E:
            LD(instruction, a8);
            break;

        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
            LD_B(instruction);
            break;

        case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E: case 0x4F:
            LD_C(instruction);
            break;

        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57:
            LD_D(instruction);
            break;

        case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F:
            LD_E(instruction);
            break;

        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67:
            LD_H(instruction);
            break;

        case 0x68: case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D: case 0x6E: case 0x6F:
            LD_L(instruction);
            break;

        case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: case 0x7E: case 0x7F:
            LD_A(instruction);
            break;

        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x77:
            LD_HL_R8(instruction);
            break;

        case 0x08:
            LD_N16_SP(a16);
            break;

        case 0x01: case 0x11: case 0x21: case 0x31:
            LD_RP(instruction, address);
            break;

        case 0x02: case 0x12: case 0x22: case 0x32:
            LD_RP_A(instruction);
            break;

        case 0x0A: case 0x1A: case 0x2A: case 0x3A:
            LD_A_RP(instruction);
            break;

        case 0xE0: case 0xF0:
            LDH_A(instruction, a8);
            break;

        case 0xF9:
            LD_SP_HL();
            break;

        // stack operations instructions
        case 0xC1: case 0xD1: case 0xE1: case 0xF1:
            POP_R16(instruction);
            break;

        case 0xC5: case 0xD5: case 0xE5: case 0xF5:
            PUSH_RP(instruction);
            break;

        // miscellaneous instructions
        case 0x2F:
            CPL();
            break;

        case 0x3F:
            CCF();
            break;

        case 0xF3:
            DI();
            break;

        default:
            std::cout << "unknown instruction!" << std::endl;
            std::exit(1);
            break;
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
