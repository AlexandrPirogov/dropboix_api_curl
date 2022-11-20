#pragma once
#include <filesystem>
#include <unordered_map>


namespace fs = std::filesystem;

enum PATHRULESTATUSES
{
    SOURCE_FILE_EXISTS,
    SOURCE_FILE_NOTEXISTS,
    SOURCE_DIRECTORY_EXISTS,
    SOURCE_DIRECTORY_NOTEXISTS,
    INCORRECT_ARGUMENTS_COUNT,
    INVALID_PATH,
    INVALID_ARGUMENTS
};

/**
 * Class to Validate types of Arguments
*/
class Rule
{
    public:
        virtual const PATHRULESTATUSES validate() = 0;
};

class PathRule : public Rule
{
    std::string localPath;
    PATHRULESTATUSES currentParseStatus;
    std::unordered_map<PATHRULESTATUSES, const char*> argumentsMessage;
    public:
        PathRule() = delete;
        /**
         * Pre-conditions: given name of existing file
         * Post-conditions: instance of PathRule created
        */
        PathRule(const std::string& localPath);

        /**
         * Pre-conditions: 
         * Post-conditions: validates given arguments
        */
        const PATHRULESTATUSES validate();

        const char* errorMessage();
};