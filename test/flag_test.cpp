#include "cpu.h"
#include <gtest/gtest.h>

TEST(FlagTest, SettersGetters) {
    CPU cpu;

    cpu.setZFlag(true);
    EXPECT_EQ(cpu.getZFlag(), true);
    cpu.setZFlag(false);
    EXPECT_EQ(cpu.getZFlag(), false);

    cpu.setHFlag(true);
    EXPECT_EQ(cpu.getHFlag(), true);
    cpu.setHFlag(false);
    EXPECT_EQ(cpu.getHFlag(), false);

    cpu.setNFlag(true);
    EXPECT_EQ(cpu.getNFlag(), true);
    cpu.setNFlag(false);
    EXPECT_EQ(cpu.getNFlag(), false);

    cpu.setCFlag(true);
    EXPECT_EQ(cpu.getCFlag(), true);
    cpu.setCFlag(false);
    EXPECT_EQ(cpu.getCFlag(), false);
}

TEST(FlagTest, SetAll) {
    CPU cpu;

    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);

    cpu.setZFlag(true);
    cpu.setHFlag(true);
    cpu.setNFlag(true);
    cpu.setCFlag(true);

    EXPECT_EQ(cpu.getZFlag(), true);
    EXPECT_EQ(cpu.getHFlag(), true);
    EXPECT_EQ(cpu.getNFlag(), true);
    EXPECT_EQ(cpu.getCFlag(), true);

    cpu.setZFlag(false);
    cpu.setHFlag(false);
    cpu.setNFlag(false);
    cpu.setCFlag(false);

    EXPECT_EQ(cpu.getZFlag(), false);
    EXPECT_EQ(cpu.getHFlag(), false);
    EXPECT_EQ(cpu.getNFlag(), false);
    EXPECT_EQ(cpu.getCFlag(), false);

}