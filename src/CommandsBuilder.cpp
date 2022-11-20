#include "CommandsBuilder.h"

template<typename T> Command* createInstance() {
     return new T; 
}

CommandsBuilder::CommandsBuilder()
{
    commandsTable = std::make_unique<CommandsMap>();
    commandsTable->insert(std::make_pair("help", createHelpCommandFunction));
    commandsTable->insert(std::make_pair("get", createGetCommandFunction));
    commandsTable->insert(std::make_pair("put", createPutCommandFunction));
    commandsTable->insert(std::make_pair("invalid", createInvalidCommandFunction));
};

std::unique_ptr<Command> CommandsBuilder::build(char* commandLine[], int argc)
{
    std::unique_ptr<CommandParserWithoutConfig> commandParser = std::make_unique<CommandParserWithoutConfig>(commandLine, argc);
    commandParser->parse();
    std::unique_ptr<Arguments> args = std::move(commandParser->getParsedArguments());
    
    //Second position -- position of command. Hadn't enough time to create it better
    auto findResult = commandsTable->find(commandLine[2]);
    std::unique_ptr<Command> cmd = findResult != commandsTable->end() ? std::move(commandsTable->operator[](commandLine[2])(args)) 
        : std::move(commandsTable->operator[]("invalid")(args)) ;
    return cmd;
};