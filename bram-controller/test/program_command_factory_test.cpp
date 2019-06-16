#include <gtest/gtest.h>
#include "program_command_factory_test.hpp"
#include "commands/command_factory.hpp"


ProgramCommandFactoryTest::ProgramCommandFactoryTest() {}

ProgramCommandFactoryTest::~ProgramCommandFactoryTest() {}

void ProgramCommandFactoryTest::SetUp() {

}

void ProgramCommandFactoryTest::TearDown() {}

TEST_F(ProgramCommandFactoryTest, ByDefaultBazTrueIsTrue) {
    char *aaa = "aaa";
    char **bbb = &aaa;
    CommandFactory * factory = new CommandFactory(2, bbb);
    factory->create();
    EXPECT_EQ(true, true);
}