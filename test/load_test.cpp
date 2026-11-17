#include <cpu.h>
#include "register_bindings.h"
#include <gtest/gtest.h>

TEST(LoadTest, LdN) { // load absolute value in register
    CPU cpu;
    cpu.LD(0x06, 16);
    ASSERT_EQ(cpu._registers[B], 16);
    cpu.LD(0x0E, 32);
    ASSERT_EQ(cpu._registers[C], 32);
}

TEST(LoadTest, LdB) {
    CPU cpu;
    cpu._registers[D] = 225;

    cpu.LD_B(0x42);

    EXPECT_EQ(cpu._registers[B], 225);
}

TEST(LoadTest, LdHL) {
    CPU cpu;

    cpu._registers[E] = 42;
    cpu.setHL(1234);

    cpu.LD_HL_R8(0x73);

    EXPECT_EQ(cpu._memory[1234], 42);
}