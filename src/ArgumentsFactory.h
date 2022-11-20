#pragma once
#include "Arguments.h"

/**
 * Class that creates instance of Arguments
*/
class ArgumentsFactory
{
    bool current_create_status;
    public:

        /**
        * Pre-conditions:
        * Post-conditions: instance of ArgumentsFactory will be created
        */
        ArgumentsFactory() = default;


        /**
        * Pre-conditions: given an existing command and args
        * Post-conditions: if command and args are correct -- returns Arguments INstance; otherwise returns InvalidArguments instances
        */
        std::unique_ptr<Arguments> createArgumentInstance(const std::string& command, const std::vector<std::string>& args);
        inline bool create_status()
        {
            return current_create_status;
        }
};