#include "cpu.h"
#include "register_bindings.h"
#include <gtest/gtest.h>

TEST(RegisterPairTest, GetAndSet) {
    CPU cpu;

    cpu.setBC(255);
    ASSERT_EQ(cpu._registers[C], 0) << "Expected register C to be 255, but was " << cpu._registers[C];
    ASSERT_EQ(cpu._registers[B], 255) << "Expected register C to be 255, but was " << cpu._registers[C];
    ASSERT_EQ(cpu.getBC(), 255) << "Expected BC to be 255, but was actually " << cpu.getBC();

    cpu.setBC(0b1010101011111111);
    EXPECT_EQ(cpu._registers[C], 0b10101010);
    EXPECT_EQ(cpu._registers[B], 0b11111111);

    cpu.setBC(65535);
    EXPECT_EQ(cpu._registers[C], 255);
    EXPECT_EQ(cpu._registers[B], 255);
}