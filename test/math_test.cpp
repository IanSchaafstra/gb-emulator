#include "cpu.h"
#include "register_bindings.h"
#include <gtest/gtest.h>

TEST(MathTest, Inc) {
    CPU cpu;
    cpu.INC(0x04);
    ASSERT_EQ(cpu._registers[B], 1);
    cpu.INC(0x04);
    ASSERT_EQ(cpu._registers[B], 2);

    // checking flags
    ASSERT_EQ(cpu.getZFlag(), false);
    ASSERT_EQ(cpu.getNFlag(), false);
    ASSERT_EQ(cpu.getCFlag(), false);

    cpu._registers[B] = 15;
    cpu.INC(0x04);
    ASSERT_EQ(cpu.getZFlag(), false);
    ASSERT_EQ(cpu.getNFlag(), false);
    ASSERT_EQ(cpu.getCFlag(), true);

    cpu._registers[C] = 255;
    cpu.INC(0x0C);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), true);
}

TEST(MathTest, IncRP) {
    CPU cpu;
    cpu.INC_RP(0x03);

    EXPECT_EQ(cpu.getBC(), 1);

    cpu.setBC(999);
    cpu.INC_RP(0x03);
    EXPECT_EQ(cpu.getBC(), 1000);

    cpu._sp = 500; // NEVER do this outside of testing
    cpu.INC_RP(0x33);
    EXPECT_EQ(cpu._sp, 501);
}

TEST(MathTest, Dec) {
    CPU cpu;

    cpu.DEC(0x05);
    EXPECT_EQ(cpu._registers[B], 255);

    cpu._registers[B] = 17;
    cpu.DEC(0x05);
    EXPECT_EQ(cpu._registers[B], 16);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);

    cpu._registers[B] = 1;
    cpu.DEC(0x05);
    EXPECT_EQ(cpu._registers[B], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);
}

TEST(MathTest, SubR) {
    CPU cpu;
    cpu._registers[A] = 135;
    cpu._registers[B] = 105;

    cpu.SUB_R(0x90);
    EXPECT_EQ(cpu._registers[A], 30);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 105;
    cpu._registers[B] = 105;
    cpu.SUB_R(0x90);

    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 105;
    cpu._registers[B] = 135;
    cpu.SUB_R(0x90);

    EXPECT_EQ(cpu._registers[A], 226);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), true);
}

TEST(MathTest, SubN) {
    CPU cpu;
    cpu._registers[A] = 90;
    cpu.SUB_N(90);
    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 0;
    cpu.SUB_N(1);
    EXPECT_EQ(cpu._registers[A], 255);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);
}

TEST(MathTest, SbcR) {
    CPU cpu;

    cpu._registers[A] = 105;
    cpu._registers[B] = 135;
    cpu.SBC_R(0x98);

    EXPECT_EQ(cpu._registers[A], 226);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu._registers[A] = 135;
    cpu._registers[B] = 105;

    cpu.SBC_R(0x98);
    EXPECT_EQ(cpu._registers[A], 29);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(MathTest, SbcN) {
    CPU cpu;
    cpu._registers[A] = 90;
    cpu.setCFlag(true);
    cpu.SBC_N(90);
    EXPECT_EQ(cpu._registers[A], 255);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu._registers[A] = 0;
    cpu.setCFlag(true);
    cpu.SBC_N(1);
    EXPECT_EQ(cpu._registers[A], 254);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);
}


TEST(MathTest, AndR) {
    CPU cpu;

    cpu._registers[A] = 10;
    cpu._registers[B] = 9;

    cpu.AND_R(0xA0);
    EXPECT_EQ(cpu._registers[A], 8);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 10;
    cpu._registers[B] = 0;

    cpu.AND_R(0xA0);
    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 108;
    cpu._registers[B] = 0;

    cpu._memory[500] = 97;
    cpu.setHL(500);

    cpu.AND_R(0xA6);
    EXPECT_EQ(cpu._registers[A], 96);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(MathTest, AndN) {
    CPU cpu;

    cpu._registers[A] = 15;
    cpu.AND_N(10);

    EXPECT_EQ(cpu._registers[A], 10);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);
    cpu._registers[A] = 15;
    cpu.AND_N(0);

    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(MathTest, OrR) {
    CPU cpu;

    cpu._registers[A] = 13;
    cpu._registers[B] = 31;
    cpu.OR_R(0xB0);

    EXPECT_EQ(cpu._registers[A], 31);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 0;
    cpu._registers[B] = 0;
    cpu.OR_R(0xB0);

    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(MathTest, CpR) {
    CPU cpu;

    cpu._registers[A] = 5;
    cpu._registers[B] = 6;
    cpu.CP_A_R(0xB8);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu._registers[A] = 130;
    cpu._registers[B] = 150;
    cpu.CP_A_R(0xB8);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu._registers[A] = 130;
    cpu._registers[B] = 0;
    cpu._memory[500] = 130;
    cpu.setHL(500);
    cpu.CP_A_R(0xBE);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(MathTest, XorR) {
    CPU cpu;
    cpu._registers[A] = 12;
    cpu._registers[B] = 3;

    cpu.XOR_R(0xA8);
    EXPECT_EQ(cpu._registers[A], 15);
    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu._registers[A] = 15;
    cpu._registers[B] = 15;

    cpu.XOR_R(0xA8);
    EXPECT_EQ(cpu._registers[A], 0);
    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(MathTest, AddHlR) {
    CPU cpu;
    cpu.setBC(2047);
    cpu.setHL(1);

    cpu.ADD_HL_R16(0x09);

    EXPECT_EQ(cpu.getHL(), 2048);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu.setBC(65534);
    cpu.setHL(1);

    cpu.ADD_HL_R16(0x09);

    EXPECT_EQ(cpu.getHL(), 65535);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);
}