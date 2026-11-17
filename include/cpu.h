#pragma once
#include <cstdint>
#include <vector>

#include "twobytes.h"

class CPU {
public:
    CPU() = default;
    void loadRom(const std::vector<uint8_t>& rom);
    void fetchInstruction();

    uint8_t _registers[8] = {}; // order: A, F, B, C, D, E, H, L
    bool _ime = false;
    uint8_t _memory[65535];
    uint16_t _sp = 0xFFFE;
    uint16_t _pc = 0x100;

    // register functions
    uint16_t getAF();
    uint16_t getBC();
    uint16_t getDE();
    uint16_t getHL();
    void setAF(uint16_t value);
    void setBC(uint16_t value);
    void setDE(uint16_t value);
    void setHL(uint16_t value);

    // flag util functions
    void setZFlag(bool state);
    void setNFlag(bool state);
    void setHFlag(bool state);
    void setCFlag(bool state);
    bool getZFlag();
    bool getNFlag();
    bool getHFlag();
    bool getCFlag();

    // jumps and subroutines
    void JP(uint16_t address);
    void JP_CONDITIONAL(uint8_t instruction, uint16_t address);
    void JR(int8_t a);
    void JR_CONDITIONAL(uint8_t instruction, int8_t value);
    void CALL(uint8_t instruction, uint16_t address);
    void RET(uint8_t instruction);
    void RST(uint8_t instruction);

    // 8-bit arithmetic and logic instructions
    void AND_R(uint8_t instruction); // AND with value in register
    void AND_N(uint8_t value); // AND with immediate value
    void DEC(uint8_t instruction);
    void INC(uint8_t instruction); // increment register
    void INC_RP(uint8_t instruction); // increment register pair
    void OR_R(uint8_t instruction);
    void CP_A_R(uint8_t instruction); // compare register A with another register
    void XOR_R(uint8_t instruction);
    void SUB_R(uint8_t instruction);
    void SUB_N(uint8_t value); // subtracts value from A
    void SBC_R(uint8_t instruction);
    void SBC_N(uint8_t value);

    // 16-bit arithmetic instructions
    void ADD_HL_R16(uint8_t instruction); // add the value in r16 to HL

    // bit shift instructions
    void RRA();
    void RRCA();
    void RLCA();

    // load instructions
    void LD_HLD_A(); // store value of A in memory at location of HL and decrement value
    void LD(uint8_t instruction, uint8_t val); // store a value in a register
    void LD_B(uint8_t instruction);
    void LD_C(uint8_t instruction);
    void LD_D(uint8_t instruction);
    void LD_E(uint8_t instruction);
    void LD_H(uint8_t instruction);
    void LD_L(uint8_t instruction);
    void LD_A(uint8_t instruction);
    void LD_HL_R8(uint8_t instruction); // store the value in register r8 into the byte pointed to by register HL
    void LD_N16_SP(uint16_t address); // store the contents of SP at n16 and n16 + 1
    void LD_RP(uint8_t instruction, uint16_t value); // load immediate value into a register pair
    void LD_RP_A(uint8_t instruction); // Store contents of register A in the memory address specified by RP
    void LD_A_RP(uint8_t instruction); // the opposite of LD_RP_A
    void LDH_A(uint8_t instruction, uint8_t address); // some documentation tells you to input a 16-bit int, but I'm not doing that since the range it operates on is 0xFF00 to 0xFFFF
    void LD_SP_HL(); // set SP to HL

    // stack operation instructions
    void POP_R16(uint8_t instruction);
    void PUSH_RP(uint8_t instruction);

    // miscellaneous instructions
    void CCF(); // flip _cFlag
    void CPL();
    void DI(); // disable interrupts
};
