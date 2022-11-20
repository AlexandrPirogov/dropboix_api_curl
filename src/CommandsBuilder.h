#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include "CommandParser.h"
#include "Command.h"

typedef std::unordered_map<std::string, std::function<std::unique_ptr<Command>(std::unique_ptr<Arguments>&)>> CommandsMap;

/**
 * Class to Build Command Instances
*/
class CommandsBuilder
{
    std::unique_ptr<CommandsMap> commandsTable;
public:

    /**
     * Pre-condition:
     * Post-condition: created instance of CommandsBuilder
    */
    CommandsBuilder();

    // Pre-cond: name of command exists in conatiner
    // Post-cond: returns Command if exists; otherwise returns InvalidCommand
    std::unique_ptr<Command> build(char* commandLine[], int argc);
private:

    /**
     * Pre-condition: Given existing type of Command
     * Post-condition: If given command exists return new instance of Command; otherwise returns Invalid Command
    */

    //GetCommand to download files from dropbox
    std::function<std::unique_ptr<Command>(std::unique_ptr<Arguments>&)> createGetCommandFunction = [](std::unique_ptr<Arguments>& arguments)
    {
        return std::make_unique<GetCommand>(arguments);
    };

    //PutCommand to upload files from dropbox
    std::function<std::unique_ptr<Command>(std::unique_ptr<Arguments>&)> createPutCommandFunction = [](std::unique_ptr<Arguments>& arguments)
    {
        return std::make_unique<PutCommand>(arguments);
    };

    //InvalidCommand to give a user message if invalid command or arguments were inputed
    std::function<std::unique_ptr<Command>(std::unique_ptr<Arguments>&)> createInvalidCommandFunction = [](std::unique_ptr<Arguments>& arguments)
    {
        return std::make_unique<InvalidCommand>(arguments);
    };

    //HelpCommand to display avaible commands
    std::function<std::unique_ptr<Command>(std::unique_ptr<Arguments>&)> createHelpCommandFunction = [](std::unique_ptr<Arguments>& arguments)
    {
        return std::make_unique<HelpCommand>(arguments);
    };
};