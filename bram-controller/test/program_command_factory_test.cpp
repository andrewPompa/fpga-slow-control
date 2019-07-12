#include <gtest/gtest.h>
#include <commands/read/read_verbose_command.hpp>
#include <commands/help/help_verbose_command.hpp>
#include "program_command_factory_test.hpp"
#include "../main/commands/command_factory.hpp"


ProgramCommandFactoryTest::ProgramCommandFactoryTest() {}

ProgramCommandFactoryTest::~ProgramCommandFactoryTest() {}

void ProgramCommandFactoryTest::SetUp() {

}

/*
 *
 * ./
./bram_controller -w
./bram_controller  --read -s
./bram_controller -r
./bram_controller -w 0x00A0000000
./bram_controller -r 0x00A0000000
./bram_controller -w 0x00A0000000 2 0x
 * */

void ProgramCommandFactoryTest::TearDown() {}

TEST_F(ProgramCommandFactoryTest, noOption) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_EQ(command, nullptr);
}


TEST_F(ProgramCommandFactoryTest, tooManyOptions) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("-w");
    args.emplace_back("--read");
    args.emplace_back("-s");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_EQ(command, nullptr);
}

TEST_F(ProgramCommandFactoryTest, writeOptionWithoutArguments) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("-w");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_EQ(command, nullptr);
}

TEST_F(ProgramCommandFactoryTest, writeOptionWithInvalidWordsArguments) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("-s");
    args.emplace_back("-w");
    args.emplace_back("10995116280000");
    args.emplace_back("1");
    args.emplace_back("MzIxMA==");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_EQ(command, nullptr);
}

TEST_F(ProgramCommandFactoryTest, readOptionWithoutArguments) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("-r");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_EQ(command, nullptr);
}

TEST_F(ProgramCommandFactoryTest, isReadCommand) {
    bool isExceptionThrown = false;
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("-r");
    auto * factory = new CommandFactory(&args);
    try {
        factory->create();
    } catch (const std::invalid_argument &e) {
        isExceptionThrown = true;
    }
    EXPECT_EQ(isExceptionThrown, true);
}

TEST_F(ProgramCommandFactoryTest, isHelpCommand) {
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("-r");
    args.emplace_back("-s");
    args.emplace_back("--help");
    auto * factory = new CommandFactory(&args);
    ProgramCommand * programCommand = factory->create();
    auto *toTest = dynamic_cast<HelpVerboseCommand *> (programCommand);
    EXPECT_NE(toTest, nullptr);
}


TEST_F(ProgramCommandFactoryTest, ReadCommandParseVerboseArguments) {
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("-r");
    args.emplace_back("0xFFFFFFFFF");
    args.emplace_back("0xFFFFFFFF");
    auto * factory = new CommandFactory(&args);
    auto * command = factory->create();
    command->execute();
}

TEST_F(ProgramCommandFactoryTest, ReadCommandParseSilentArguments) {
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("--silent");
    args.emplace_back("--read");
    long value = 0xFFFFFFFFFF;
    args.emplace_back("0xFFFFFFFFF");
    args.emplace_back("0xFFFFFFFF");
    auto * factory = new CommandFactory(&args);
    auto * command = factory->create();
    command->execute();
}