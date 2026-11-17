#include "cpu.h"
#include "register_bindings.h"

#include <iostream>

void CPU::AND_R(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0xA0:
            value = _registers[B];
            break;
        case 0xA1:
            value = _registers[C];
            break;
        case 0xA2:
            value = _registers[D];
            break;
        case 0xA3:
            value = _registers[E];
            break;
        case 0xA4:
            value = _registers[H];
            break;
        case 0xA5:
            value = _registers[L];
            break;
        case 0xA6:
            value = _memory[getHL()];
            break;
        case 0xA7:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid AND! Attempted to AND with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[A] &= value;

    if (_registers[A] == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(false);
    setHFlag(true);
    setCFlag(false);

    _pc++;
}

void CPU::AND_N(uint8_t value) {
    uint8_t valueToSet = _registers[A] & value;

    if (valueToSet == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }
    setNFlag(false);
    setHFlag(true);
    setCFlag(false);
    _registers[A] = valueToSet;

    _pc++;
}

void CPU::DEC(uint8_t instruction) {
    std::cout << "dec" << std::endl;
    uint8_t a;
    uint8_t b = 1;
    switch (instruction) {
        case 0x05:
            a = _registers[B];
            if (_registers[B] == 0) {
                _registers[B] = 0xFF;
            } else {
                _registers[B]--;
            }
            break;
        case 0x0D:
            a = _registers[C];
            _registers[C]--;
            break;
        case 0x15:
            a = _registers[D];
            _registers[D]--;
            break;
        case 0x1D:
            a = _registers[E];
            _registers[E]--;
            break;
        case 0x25:
            a = _registers[H];
            _registers[H]--;
            break;
        case 0x2D:
            a = _registers[L];
            _registers[L]--;
            break;
        case 0x3D:
            a = _registers[A];
            _registers[A]--;
            break;
        default:
            std::cerr << "Invalid decrement! Attempted to decrement with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    uint8_t result = a - b;
    // uint8_t half_carry = (a ^ (-b) ^ result) & 0x10;
    uint8_t half_carry = (a & 0xF) - (b & 0xF) < 0;

    // std::cout << "result: " << std::hex << static_cast<unsigned short>(result) << std::endl;
    // std::cout << "half carry: " << std::hex << static_cast<unsigned short>(half_carry) << std::endl;

    if (result == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(true);

    if (half_carry != 0) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    _pc++;
}

void CPU::INC(uint8_t instruction) {
    uint8_t a;
    uint8_t b = 1;
    switch (instruction) {
        case 0x04:
            a = _registers[B];
            _registers[B]++;
            break;
        case 0x0C:
            a = _registers[C];
            _registers[C]++;
            break;
        case 0x14:
            a = _registers[D];
            _registers[D]++;
            break;
        case 0x1C:
            a = _registers[E];
            _registers[E]++;
            break;
        case 0x24:
            a = _registers[H];
            _registers[H]++;
            break;
        case 0x2C:
            a = _registers[L];
            _registers[L]++;
            break;
        case 0x3C:
            a = _registers[A];
            _registers[A]++;
            break;
        default:
            std::cerr << "Invalid increment! Attempted to increment with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    uint8_t result = a + b;
    // uint8_t half_carry = (a ^ b ^ result) & 0x10;
    uint8_t half_carry = (a & 0xF) + (b & 0xF) > 0xF;

    // std::cout << "result: " << std::hex << static_cast<unsigned short>(result) << std::endl;
    // std::cout << "half carry: " << std::hex << static_cast<unsigned short>(half_carry) << std::endl;

    if (result == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(false);

    if (half_carry != 0) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }

    _pc++;
}

void CPU::INC_RP(uint8_t instruction) {
    switch (instruction) {
        case 0x03:
            setBC(getBC() + 1);
            break;
        case 0x13:
            setDE(getDE() + 1);
            break;
        case 0x23:
            setHL(getHL() + 1);
            break;
        case 0x33:
            _sp++;
            break;
        default:
            std::cerr << "Invalid increment! Attempted to increment RP with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _pc++;
}

void CPU::OR_R(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0xB0:
            value = _registers[B];
            break;
        case 0xB1:
            value = _registers[C];
            break;
        case 0xB2:
            value = _registers[D];
            break;
        case 0xB3:
            value = _registers[E];
            break;
        case 0xB4:
            value = _registers[H];
            break;
        case 0xB5:
            value = _registers[L];
            break;
        default:
            std::cerr << "Invalid OR function! Attempted to OR with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }
    uint8_t result = value | _registers[A];

    if (result == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }
    setNFlag(false);
    setHFlag(false);
    setCFlag(false);

    _registers[A] = result;
    _pc++;
}

void CPU::CP_A_R(uint8_t instruction) {
    uint8_t value;

    switch (instruction) {
        case 0xB8:
            value = _registers[B];
            break;
        case 0xB9:
            value = _registers[C];
            break;
        case 0xBA:
            value = _registers[D];
            break;
        case 0xBB:
            value = _registers[E];
            break;
        case 0xBC:
            value = _registers[H];
            break;
        case 0xBD:
            value = _registers[L];
            break;
        case 0xBE:
            value = _memory[getHL()];
            break;
        case 0xBF:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid CP function! Attempted to CP with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    if (_registers[A] == value) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(true);

    bool half_carry = (_registers[A] & 0xF) - (value & 0xF) < 0;
    //if ((_registers[A] >> 4) < (value >> 4)) {
    if (half_carry) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    if (_registers[A] < value) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }

    _pc++;
}

void CPU::XOR_R(uint8_t instruction) {
    auto a = _registers[A];
    uint8_t b;
    switch (instruction) {
        case 0xA8:
            b = _registers[B];
            break;
        case 0xA9:
            b = _registers[C];
            break;
        case 0xAA:
            b = _registers[D];
            break;
        case 0xAB:
            b = _registers[E];
            break;
        case 0xAC:
            b = _registers[H];
            break;
        case 0xAD:
            b = _registers[L];
            break;
        case 0xAE:
            b = _memory[getHL()];
            break;
        case 0xAF:
            b = _registers[A];
            break;
        default:
            std::cerr << "Invalid XOR function! Attempted to XOR with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    _registers[A] = a ^ b;

    if (_registers[A] == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }
    setNFlag(false);
    setHFlag(false);
    setCFlag(false);

    _pc++;
    std::cout << "XOR Register A" << std::endl;
}

void CPU::SUB_R(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x90:
            value = _registers[B];
            break;
        case 0x91:
            value = _registers[C];
            break;
        case 0x92:
            value = _registers[D];
            break;
        case 0x93:
            value = _registers[E];
            break;
        case 0x94:
            value = _registers[H];
            break;
        case 0x95:
            value = _registers[L];
            break;
        case 0x96:
            value = _memory[getHL()];
            break;
        case 0x97:
            value = _registers[A];
            break;
        default:
            std::cerr << "Invalid SUB function! Attempted to SUB with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    uint8_t a = _registers[A];

    uint8_t result = a - value;
    // uint8_t half_carry = (a ^ (-value) ^ result) & 0x10;
    bool half_carry = (a & 0xF) - (value & 0xF) < 0;

    if (result == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(true);

    if (half_carry) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    if (value > a) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }


    _registers[A] -= value;

    _pc++;
}

void CPU::SBC_R(uint8_t instruction) {
    uint8_t value;
    switch (instruction) {
        case 0x98:
            value = _registers[B];
            break;
        case 0x99:
            value = _registers[C];
            break;
        case 0x9A:
            value = _registers[D];
            break;
        case 0x9B:
            value = _registers[E];
            break;
        case 0x9C:
            value = _registers[H];
            break;
        case 0x9D:
            value = _registers[L];
            break;
        case 0x9E:
            value = _memory[getHL()];
            break;
        case 0x9F:
            value = _registers[A];
            break;

        default:
            std::cerr << "Invalid SBC function! Attempted to SBC with instruction: " << instruction << " which is not a valid instruction!" << std::endl;
            return;
    }

    if (getCFlag()) {
        value++;
    }

    uint8_t a = _registers[A];

    uint8_t result = a - value;
    // uint8_t half_carry = (a ^ (-value) ^ result) & 0x10;
    bool half_carry = (a & 0xF) - (value & 0xF) < 0;

    if (result == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(true);

    if (half_carry) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    if (value > a) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }


    _registers[A] -= value;

    _pc++;
}

void CPU::SUB_N(uint8_t value) {
    uint8_t a = _registers[A];
    uint8_t result = a - value;
    //uint8_t half_carry = (a ^ (-value) ^ result) & 0x10;
    bool half_carry = (a & 0xF) - (value & 0xF) < 0;
    _registers[A] -= value;

    if (_registers[A] == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(true);

    if (half_carry) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    if (value > a) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }

    _pc++;
}

void CPU::SBC_N(uint8_t value) {
    uint8_t a = _registers[A];
    uint8_t b = value;
    if (getCFlag()) {
        b++;
    }
    uint8_t result = a - b;
    // uint8_t half_carry = (a ^ (-value) ^ result) & 0x10;
    bool half_carry = (a & 0xF) - (b & 0xF) < 0;
    _registers[A] -= b;

    if (_registers[A] == 0) {
        setZFlag(true);
    } else {
        setZFlag(false);
    }

    setNFlag(true);

    if (half_carry) {
        setHFlag(true);
    } else {
        setHFlag(false);
    }

    if (b > a) {
        setCFlag(true);
    } else {
        setCFlag(false);
    }

    _pc++;
}
