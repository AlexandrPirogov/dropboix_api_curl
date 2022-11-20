#pragma once
#include <vector>
#include <string>
#include "Rules.h"

/**
 * Type to incapsulate commands arguments and validate 'em
*/
class Arguments
{
    protected:
        std::vector<std::string> args;
    public:
        Arguments() = default;

        /**
         * Pre-conditions: given container of inputed arguments for command
         * Post-conditions: created instance of Arguments
        */
        Arguments(const std::vector<std::string>& givenArgs);
        
        
        /**
        * Pre-conditions: given an index > 0 and < container.size()
        * Post-conditions: returns value stored at index
        */    
        inline const std::string& at(int index) noexcept
        {
            return args[index];
        }


        /**
        * Pre-conditions: 
        * Post-conditions: validting given arguments;
        */
        virtual bool validate()
        {
            return false;
        };


        /**
        * Pre-conditions:
        * Post-conditions: return count of given arguments
        */
        const size_t size() const;

        std::string& operator[](int index)
        {
            return args[index];
        };

        virtual const char* errorMessage() = 0;
        virtual inline PATHRULESTATUSES status() = 0;
};

/**
 * Class that handles arguments of Get Command to downlaod files from DropBox
*/
class GetCommandArguments : public Arguments
{   
        PATHRULESTATUSES parseStatus;
        std::unique_ptr<PathRule> pathRule;
    public:
        GetCommandArguments() = delete;
        GetCommandArguments(const std::vector<std::string>& givenArgs);

        bool validate();
        inline PATHRULESTATUSES status() 
        {
            return parseStatus;
        }

         virtual const char* errorMessage();
};

/**
 * Class that handles arguments of Put Command to upload files to Dropbox
*/
class PutCommandArguments : public Arguments
{   
        PATHRULESTATUSES parseStatus;
        std::unique_ptr<PathRule> pathRule;
    public:
        PutCommandArguments() = delete;
        PutCommandArguments(const std::vector<std::string>& givenArgs);

        bool validate();
        inline PATHRULESTATUSES status() 
        {
            return parseStatus;
        }

        virtual const char* errorMessage();
};

/**
 * Class that needs if arguments were incorrect
*/
class InvalidCommandArguments : public Arguments
{
        std::unique_ptr<PathRule> pathRule;
    public:
        InvalidCommandArguments() = default;
        InvalidCommandArguments(const std::vector<std::string>& givenArgs);

        inline bool validate()
        {
            return false;
        };

        const char* errorMessage()
        {
            return "Invalid args or Command\n";
        }


        inline PATHRULESTATUSES status() 
        {
            return INVALID_ARGUMENTS;
        }
};