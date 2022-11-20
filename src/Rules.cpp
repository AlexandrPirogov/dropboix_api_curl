#include "Rules.h"


PathRule::PathRule(const std::string& localPath) : localPath(localPath)
{

    argumentsMessage[PATHRULESTATUSES::SOURCE_DIRECTORY_NOTEXISTS] = "Local directory doesn't exists!";
    argumentsMessage[PATHRULESTATUSES::SOURCE_FILE_NOTEXISTS] = "Local file doesn't exists!";
};

#include <iostream>
const PATHRULESTATUSES PathRule::validate()
{
    
    auto current = std::filesystem::path(localPath.c_str());
    auto dir = current;
    dir.remove_filename();
    if(fs::is_directory(dir))
    {
        if(fs::is_regular_file(current))
            currentParseStatus = SOURCE_FILE_EXISTS;
        else
            currentParseStatus = SOURCE_FILE_NOTEXISTS;
    }   else 
        currentParseStatus= SOURCE_DIRECTORY_NOTEXISTS;

    return currentParseStatus;
};

const char* PathRule::errorMessage()
{
    return argumentsMessage[currentParseStatus];
};