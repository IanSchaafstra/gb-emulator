#include "cpu.h"
#include "register_bindings.h"
#include <gtest/gtest.h>

TEST(BitShiftTest, RRA) {
    CPU cpu;

    cpu._registers[A] = 0b00000010;
    cpu.RRA();

    EXPECT_EQ(cpu._registers[A], 1);

    cpu.RRA();
    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu.RRA();
    EXPECT_EQ(cpu._registers[A], 0b10000000);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu.setCFlag(true);

    cpu.RRA();
    EXPECT_EQ(cpu._registers[A], 0b11000000);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(BitShiftTest, RRCA) {
    CPU cpu;

    cpu._registers[A] = 0b01010101;

    cpu.RRCA();

    EXPECT_EQ(cpu._registers[A], 0b10101010);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu.RRCA();

    EXPECT_EQ(cpu._registers[A], 0b01010101);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(BitShiftTest, RLCA) {
    CPU cpu;

    cpu._registers[A] = 0b10000000;

    cpu.RLCA();

    EXPECT_EQ(cpu._registers[A], 0b00000001);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu._registers[A] = 0b10000100;

    cpu.RLCA();

    EXPECT_EQ(cpu._registers[A], 0b00001001);
    EXPECT_EQ(cpu.getCFlag(), true);
}