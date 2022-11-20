#include "CommandParser.h"

CommandParserWithoutConfig::CommandParserWithoutConfig(char* cmd[], int argc)
{
    //Bad decision. Hadn't enough time to make it better
    givenCommand = std::string(cmd[2]);
    for(int i = 3; i < argc; i++)
        args.push_back(cmd[i]);
};


void CommandParserWithoutConfig::parse()
{
    std::unique_ptr<ArgumentsFactory> argumentsFactory = std::make_unique<ArgumentsFactory>();
    arguments = std::move(argumentsFactory->createArgumentInstance(givenCommand, args));
    
    argumentsFactory->create_status() == true ? 
        current_parse_status = PARSE_STATUS_OK :
        current_parse_status = PARSE_STATUS_ERROR;
};

std::unique_ptr<Arguments>& CommandParserWithoutConfig::getParsedArguments()
{
    return arguments;
};