#include <gtest/gtest.h>
#include <memory>
#include "CommandParser.h"
#include "Command.h"


char* commandWithoutArgs[4] = {"dropbox", "login", "password", "get"};
char* getCommandWithArgs[6] = {"dropbox", "login", "password", "get", "/", "/"};

TEST(CommandParseWithoutConfigTests, CreatingCommandParseWithoutConfig) {
    std::unique_ptr<CommandParserWithoutConfig> commandParser = std::make_unique<CommandParserWithoutConfig>(commandWithoutArgs, 4);
    ASSERT_EQ(commandParser->parse_status(), commandParser->PARSE_STATUS_NIL);
}

TEST(CommandParseWithoutConfigTests, ParsingCommandParseWithoutConfig) {
    std::unique_ptr<CommandParserWithoutConfig> commandParser = std::make_unique<CommandParserWithoutConfig>(commandWithoutArgs, 4);
    commandParser->parse();
    ASSERT_EQ(commandParser->parse_status(), commandParser->PARSE_STATUS_OK);
}

TEST(CommandParseWithoutConfigTests, ParsingGetCommandArgs) {
    std::unique_ptr<CommandParserWithoutConfig> commandParser = std::make_unique<CommandParserWithoutConfig>(getCommandWithArgs, 6);
    commandParser->parse();
    ASSERT_EQ(commandParser->parse_status(), commandParser->PARSE_STATUS_OK);
}
