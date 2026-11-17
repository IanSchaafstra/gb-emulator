#include "cpu.h"
#include <gtest/gtest.h>

TEST(SubroutineTest, Call) {
    CPU cpu;

    cpu._pc = 500;
    cpu._memory[503] = 13;
    cpu._memory[504] = 37;

    cpu.CALL(0xCD, 32000);

    EXPECT_EQ(cpu._memory[cpu._sp + 1], 13);
    EXPECT_EQ(cpu._memory[cpu._sp], 37);
    EXPECT_EQ(cpu._pc, 32000);
}

TEST(SubroutineTest, CallConditional) {
    CPU cpu;

    cpu._pc = 500;
    cpu._sp = 20000;
    cpu._memory[503] = 13;
    cpu._memory[504] = 37;

    cpu.CALL(0xCC, 32000);

    EXPECT_EQ(cpu._pc, 503);

    cpu._pc = 500;
    cpu.setZFlag(true);

    cpu.CALL(0xCC, 32000);

    EXPECT_EQ(cpu._memory[cpu._sp + 1], 13);
    EXPECT_EQ(cpu._memory[cpu._sp], 37);
    EXPECT_EQ(cpu._pc, 32000);
    EXPECT_EQ(cpu._sp, 19998);
}

TEST(SubroutineTest, Ret) {
    CPU cpu;

    cpu._pc = 500;
    cpu._sp = 20000;
    cpu._memory[503] = 13;
    cpu._memory[504] = 37;

    cpu.CALL(0xCD, 32000); // I know I shouldn't make test rely on external functionality, but whatever. I have a test for CALL, I know it works.

    cpu.RET(0xC9);

    EXPECT_EQ(cpu._pc, 3365);
    EXPECT_EQ(cpu._sp, 20000);
}

TEST(SubroutineTest, RetConditional) {
    CPU cpu;

    cpu._pc = 500;
    cpu._sp = 20000;
    cpu._memory[503] = 13;
    cpu._memory[504] = 37;

    cpu.CALL(0xCD, 32000);


    cpu.setZFlag(true);

    cpu.RET(0xC0);

    EXPECT_EQ(cpu._pc, 32001);

    cpu.setZFlag(false);

    cpu.RET(0xC0);

    EXPECT_EQ(cpu._pc, 3365);
    EXPECT_EQ(cpu._sp, 20000);
}