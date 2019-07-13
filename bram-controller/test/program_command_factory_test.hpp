#ifndef BRAM_CONTROLLER_PROJECT_PROGRAM_COMMAND_FACTORY_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_PROGRAM_COMMAND_FACTORY_TEST_HPP


#include "../main/commands/command_factory.hpp"

class ProgramCommandFactoryTest : public ::testing::Test {
protected:

    // You can do set-up work for each test here.
    ProgramCommandFactoryTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~ProgramCommandFactoryTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

private:
    CommandFactory *factory;
};


#endif //BRAM_CONTROLLER_PROJECT_PROGRAM_COMMAND_FACTORY_TEST_HPP
