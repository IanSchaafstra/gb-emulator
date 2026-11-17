#include "cpu.h"
#include <gtest/gtest.h>

TEST(JumpsTest, Jr) {
    CPU cpu;

    cpu._pc = 500;

    cpu.JR(50);

    EXPECT_EQ(cpu._pc, 550);
}

TEST(JumpsTest, JrConditional) {
    CPU cpu;

    cpu.setZFlag(true);
    cpu._pc = 500;
    cpu.JR_CONDITIONAL(0x28, 50);

    EXPECT_EQ(cpu._pc, 550);

    cpu.setZFlag(false);
    cpu.setCFlag(true);

    cpu.JR_CONDITIONAL(0x38, 50);

    EXPECT_EQ(cpu._pc, 600);

    cpu.setZFlag(false);
    cpu.setCFlag(true);

    cpu.JR_CONDITIONAL(0x20, 50);

    EXPECT_EQ(cpu._pc, 650);

    cpu.setZFlag(true);
    cpu.setCFlag(false);

    cpu.JR_CONDITIONAL(0x30, 50);

    EXPECT_EQ(cpu._pc, 700);
}

TEST(JumpsTest, Jp) {
    CPU cpu;

    uint8_t lower = 12;
    uint8_t higher = 32;

    uint16_t address = (higher << 8) | lower; // 8204

    cpu.JP(address);

    EXPECT_EQ(cpu._pc, 8204);
}

TEST(JumpsTest, JpConditional) {
    CPU cpu;

    cpu.setCFlag(true);
    cpu._pc = 500;

    cpu.JP_CONDITIONAL(0xD2, 550);

    EXPECT_EQ(cpu._pc, 503);

    cpu.JP_CONDITIONAL(0xDA, 550);

    EXPECT_EQ(cpu._pc, 550);

    cpu.setCFlag(false);
    cpu.setZFlag(true);

    cpu._pc = 700;

    cpu.JP_CONDITIONAL(0xC2, 600);

    EXPECT_EQ(cpu._pc, 703);

    cpu.JP_CONDITIONAL(0xCA, 600);

    EXPECT_EQ(cpu._pc, 600);
}