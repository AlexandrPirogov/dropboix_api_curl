#include "Arguments.h"


Arguments::Arguments(const std::vector<std::string>& givenArgs) : args(givenArgs)
{
   
};

const size_t Arguments::size() const
{
    return args.size();
};


GetCommandArguments::GetCommandArguments(const std::vector<std::string>& givenArgs) : Arguments(givenArgs)
{
    //Bad decision. Hadn't enough time to make it better
    if(givenArgs.size() >= 1)
        pathRule = std::make_unique<PathRule>(givenArgs[1]);
    else
        throw std::runtime_error("Incorrect number of arguments!\n");
        
};

bool GetCommandArguments::validate()
{
    parseStatus = pathRule->validate();
    return parseStatus != PATHRULESTATUSES::SOURCE_FILE_NOTEXISTS && parseStatus != PATHRULESTATUSES::SOURCE_DIRECTORY_NOTEXISTS;
};

const char* GetCommandArguments::errorMessage()
{
    return pathRule->errorMessage();
}

PutCommandArguments::PutCommandArguments(const std::vector<std::string>& givenArgs): Arguments(givenArgs)
{
    //Bad decision. Hadn't enough time to make it better
    if(givenArgs.size() >= 1)
        pathRule = std::make_unique<PathRule>(givenArgs[0]);
    else
        throw std::runtime_error("Incorrect number of arguments!\n");
};

bool PutCommandArguments::validate()
{
    parseStatus = pathRule->validate();
    return parseStatus != PATHRULESTATUSES::SOURCE_FILE_NOTEXISTS && parseStatus != PATHRULESTATUSES::SOURCE_DIRECTORY_NOTEXISTS;
};


const char* PutCommandArguments::errorMessage()
{
    return pathRule->errorMessage();
}


InvalidCommandArguments::InvalidCommandArguments(const std::vector<std::string>& givenArgs)
{
    
};