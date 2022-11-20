#include "Command.h"


HelpCommand::HelpCommand()
{
    commandHelp = COMMANDS::HELP;
};

HelpCommand::HelpCommand(std::unique_ptr<Arguments>& givenArgs)
{
    commandHelp = COMMANDS::HELP;
    args = std::move(givenArgs);
};

HelpCommand::HelpCommand(COMMANDS command)
{
    commandHelp = command;
};

HelpCommand::HelpCommand(COMMANDS command, Arguments& args)
{
    commandHelp = command;
};

void HelpCommand::execute(RequestHandler* handler){

};

string HelpCommand::strForPrint()
{
    return helpInfo.find(commandHelp)->second;
};

InvalidCommand::InvalidCommand(std::unique_ptr<Arguments>& givenArgs)
{
    args = std::move(givenArgs);
};

void InvalidCommand::execute(RequestHandler* handler){
    validateArgs();
};

string InvalidCommand::strForPrint()
{
    return std::string("Invalid command");
};

void InvalidCommand::validateArgs()
{

    std::string ArgError = "\n\n\n+-------------ERROR!-------------+\n";
    ArgError += "|   Inputed command not exists!  |\n";
    ArgError +=  "+--------------------------------+\n";
    throw std::runtime_error(ArgError);
 
};

GetCommand::GetCommand(COMMANDS command, std::unique_ptr<Arguments>& givenArgs)
{
    commandGet = COMMANDS::GET;
    args = std::move(givenArgs);
};

GetCommand::GetCommand(std::unique_ptr<Arguments>& givenArgs)
{
    commandGet = COMMANDS::GET;
    args = std::move(givenArgs);
};

void GetCommand::execute(RequestHandler* handler){
    validateArgs();
    handler->handleRequest(this);
};

string GetCommand::strForPrint()
{
    validateArgs();
    return std::string("Get command");
};

void GetCommand::validateArgs()
{
    bool argsIsValid = args->validate();
    if(args->status() == PATHRULESTATUSES::SOURCE_DIRECTORY_NOTEXISTS)
    {
        std::string ArgError = "\n\n\n+-------------ERROR!-------------+\n";
        ArgError += "|"; ArgError+= args->errorMessage(); ArgError += " |\n";
        ArgError +=  "+--------------------------------+\n";
        throw std::runtime_error(ArgError);
    }
        
};

PutCommand::PutCommand(std::unique_ptr<Arguments>& givenArgs)
{
    commandPut= COMMANDS::PUT;
    args = std::move(givenArgs);
};

void PutCommand::execute(RequestHandler* handler)
{

    validateArgs();
    handler->handleRequest(this);
};

string PutCommand::strForPrint()
{
    validateArgs();
    return std::string("Put command");
};


void PutCommand::validateArgs()
{
    bool argsIsValid = args->validate();
    if(!argsIsValid)
    {
        std::string ArgError = "\n\n\n+-------------ERROR!-------------+\n";
        ArgError += "|"; ArgError+= args->errorMessage(); ArgError += "      |\n";
        ArgError +=  "+--------------------------------+\n";
        throw std::runtime_error(ArgError);
    }
    
};