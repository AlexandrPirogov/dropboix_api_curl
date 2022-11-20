#include "ArgumentsFactory.h"

std::unique_ptr<Arguments> ArgumentsFactory::createArgumentInstance(const std::string& command, const std::vector<std::string>& args)
{
    current_create_status = true;
    //ADT dictionary would be great here
    if(command == "get")
    {
        return std::make_unique<GetCommandArguments>(args);
    } 
    if(command == "put")
    {
        return std::make_unique<PutCommandArguments>(args);
    }
    current_create_status = false;
    return std::make_unique<InvalidCommandArguments>();
};