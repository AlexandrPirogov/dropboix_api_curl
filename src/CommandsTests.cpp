#include <gtest/gtest.h>
#include <memory>
#include "Command.h"



TEST(CommandsTests, CreatingHelpCommand) {
    std::unique_ptr<Command> helpCommand = std::make_unique<HelpCommand>();
    ASSERT_EQ(helpCommand->strForPrint(), helpInfo.find(COMMANDS::HELP)->second);
}

TEST(CommandsTests, HelpWithGetCommand) {
    std::unique_ptr<Command> helpCommand = std::make_unique<HelpCommand>(COMMANDS::GET);
    ASSERT_EQ(helpCommand->strForPrint(), helpInfo.find(COMMANDS::GET)->second);
}


TEST(CommandsTests, HelpWithPutCommand) {
    std::unique_ptr<Command> helpCommand = std::make_unique<HelpCommand>(COMMANDS::PUT);
    ASSERT_EQ(helpCommand->strForPrint(), helpInfo.find(COMMANDS::PUT)->second);
}
