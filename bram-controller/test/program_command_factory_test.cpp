#include <gtest/gtest.h>
#include <commands/read/read_verbose_command.hpp>
#include <commands/help/help_verbose_command.hpp>
#include "program_command_factory_test.hpp"
#include "../main/commands/command_factory.hpp"
#include <climits>

ProgramCommandFactoryTest::ProgramCommandFactoryTest() {}

ProgramCommandFactoryTest::~ProgramCommandFactoryTest() {}

void ProgramCommandFactoryTest::SetUp() {

}

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

TEST_F(ProgramCommandFactoryTest, writeOptionValidArguments) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("-w");
    args.emplace_back("0xA0000000");
    args.emplace_back("0x3");
    args.emplace_back("0xFFAAFFAA00110011BB22BB22");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_NE(command, nullptr);
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
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("-r");
    auto * factory = new CommandFactory(&args);
    ProgramCommand* command = factory->create();
    EXPECT_EQ(command, nullptr);
}

TEST_F(ProgramCommandFactoryTest, isHelpCommand) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
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
    args.emplace_back("bram_controller");
    args.emplace_back("-r");
    args.emplace_back("0xFFFFFFFFF");
    args.emplace_back("0xFFFFFFFF");
    auto * factory = new CommandFactory(&args);
    auto * command = factory->create();
    EXPECT_NE(command, nullptr);
}

TEST_F(ProgramCommandFactoryTest, ReadCommandParseSilentArguments) {
    std::vector<std::string> args;
    args.emplace_back("bram_controller");
    args.emplace_back("--silent");
    args.emplace_back("--read");
    args.emplace_back("12345");
    args.emplace_back("14");
    auto * factory = new CommandFactory(&args);
    auto * command = factory->create();
    EXPECT_NE(command, nullptr);
}