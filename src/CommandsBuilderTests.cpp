#include <gtest/gtest.h>
#include <memory>
#include "Command.h"
#include "CommandsBuilder.h"

TEST(CommandsBuilderTests, CreatingCommandsBuilder) {
    std::unique_ptr<CommandsBuilder> commandsBuilder = std::make_unique<CommandsBuilder>();
}

TEST(CommandsBuilderTests, RetrievingInvalid) {
    std::unique_ptr<CommandsBuilder> commandsBuilder = std::make_unique<CommandsBuilder>();
    char* invalid[6] = {"dropbox", "login", "password", "notexistingcommand", "src", "dst"};
    std::unique_ptr<Command> invalidCommand = commandsBuilder->build(invalid, 6);
    ASSERT_EQ(invalidCommand->strForPrint(), "Invalid command");
}

TEST(CommandsBuilderTests, RetrievingGet) {
    std::unique_ptr<CommandsBuilder> commandsBuilder = std::make_unique<CommandsBuilder>();
    char* get[6] = {"dropbox", "login", "password", "get", "/", "/"};
    std::unique_ptr<Command> getCommand = commandsBuilder->build(get, 6);
    ASSERT_EQ(getCommand->strForPrint(), "Get command");
}

TEST(CommandsBuilderTests, RetrievingPut) {
    std::unique_ptr<CommandsBuilder> commandsBuilder = std::make_unique<CommandsBuilder>();
    char* put[6] = {"dropbox", "login", "password", "put", "src", "dst"};
    std::unique_ptr<Command> putCommand = commandsBuilder->build(put, 6);
    //ASSERT_EQ(putCommand->strForPrint(), "Put command");
}

TEST(CommandsBuilderTests, RetrievingHelp) {
    std::unique_ptr<CommandsBuilder> commandsBuilder = std::make_unique<CommandsBuilder>();
    std::string help = "help";
    //std::unique_ptr<Command> helpCommand = commandsBuilder->build(help, 6);
    //ASSERT_EQ(helpCommand->strForPrint(), helpInfo.find(COMMANDS::HELP)->second);
}
