#pragma once
#include <vector>
#include <string>
#include "ArgumentsFactory.h"

enum CommandParserStatusesEnum
{
    PARSE_STATUS_NIL = -1, PARSE_STATUS_OK = 0, PARSE_STATUS_ERROR = 1
};

/**
 * Type for parsing inputed commands
*/
class CommandParser
{
protected:
    short current_parse_status;
    public:

        const short PARSE_STATUS_NIL = CommandParserStatusesEnum::PARSE_STATUS_NIL;
        const short PARSE_STATUS_OK = CommandParserStatusesEnum::PARSE_STATUS_OK;
        const short PARSE_STATUS_ERROR = CommandParserStatusesEnum::PARSE_STATUS_ERROR;

        CommandParser() = default;

        CommandParser(char* cmd[])
        {
            current_parse_status = PARSE_STATUS_NIL;
        };

        virtual void parse() = 0;

        const inline short parse_status()
        {
            return current_parse_status;
        }
};

class CommandParserWithoutConfig : public CommandParser
{
    std::string givenCommand;
    std::vector<std::string> args;
    std::unique_ptr<Arguments> arguments;
public:
    CommandParserWithoutConfig() = delete;

    /**
     * Pre-conditions: given inputed words and count of inputed words
     * Post-conditions: created instance of Parser
    */
    CommandParserWithoutConfig(char* cmd[], int argc);


    /**
     * Pre-conditions:
     * Post-conditions: creates Arguments Instance
    */
    void parse();


    /**
     * Pre-conditions:
     * Post-conditions: returns ptr of created Arguments Instance
    */
    std::unique_ptr<Arguments>& getParsedArguments();
};