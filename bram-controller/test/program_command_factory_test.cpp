#include <gtest/gtest.h>
#include <commands/read/read_verbose_command.hpp>
#include <commands/help/help_verbose_command.hpp>
#include "program_command_factory_test.hpp"
#include "../main/commands/command_factory.hpp"


ProgramCommandFactoryTest::ProgramCommandFactoryTest() {}

ProgramCommandFactoryTest::~ProgramCommandFactoryTest() {}

void ProgramCommandFactoryTest::SetUp() {

}

void ProgramCommandFactoryTest::TearDown() {}

TEST_F(ProgramCommandFactoryTest, isReadCommand) {
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("-r");
    auto * factory = new CommandFactory(&args);
    ProgramCommand * programCommand = factory->create();
    auto *toTest = dynamic_cast<ReadVerboseCommand *> (programCommand);
    EXPECT_NE(toTest, nullptr);
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

TEST_F(ProgramCommandFactoryTest, tooManyOptions) {
    bool isExceptionThrown = false;
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("-r");
    args.emplace_back("--write");
    args.emplace_back("-s");
    auto * factory = new CommandFactory(&args);
    try {
        factory->create();
    } catch (const std::invalid_argument &e) {
        isExceptionThrown = true;
    }
    EXPECT_EQ(isExceptionThrown, true);
}

TEST_F(ProgramCommandFactoryTest, ReadCommandParseArguments) {
    std::vector<std::string> args;
    args.emplace_back("program-name");
    args.emplace_back("-r");
    args.emplace_back("0xFFFFFFFFF");
    args.emplace_back("0xFFFFFFFF");
    auto * factory = new CommandFactory(&args);
    auto * command = factory->create();
    command->execute();
}