#include "cpu.h"
#include "register_bindings.h"

void CPU::CCF() {
    setNFlag(false);
    setHFlag(false);
    setCFlag(!getCFlag());

    _pc++;
}

void CPU::CPL() {
    _registers[A] = ~_registers[A];

    setNFlag(true);
    setHFlag(true);

    _pc++;
}

void CPU::DI() {
    _ime = false;
    _pc++;
}
