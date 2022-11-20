#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include "Arguments.h"
#include <nlohmann/json.hpp>
#include "curl/RequestHandler.h"

using std::string;

enum COMMANDS
{
    HELP, GET, PUT, INVALID
};

const string putDescription = "-- put <src_path> <dst_path>: "
                                   "uploads file to dropbox in <src_path> from the <dst_path> on your PC\n";
const string getDescription = "-- get <src_path> <dst_path>: "
                                   "downloads file from dropbox in <src_path> to the <dst_path> on your PC\n";
const string helpDescription = getDescription + "\n" + putDescription + "\n";

const std::unordered_map<COMMANDS, string> helpInfo =
{
    {COMMANDS::GET, getDescription},
    {COMMANDS::HELP, helpDescription},
    {COMMANDS::PUT, putDescription},
};


//Forward declaration
class RequestHandler;

/**
 * Type for inputed commands
 * Incapsulets arguments, description 
*/
class Command
{
public:

    /**
     * Pre-conditions: given an RequestHandler pointer
     * Post-conditions: Command will be executed
    */
    virtual void execute(RequestHandler* handler) = 0;

    /**
     * Pre-conditions:
     * Post-conditions: validates inputed arguments of commands
    */
    virtual void validateArgs() = 0;

    /**
     * Pre-conditions:
     * Post-conditions: return string representation of command
    */
    virtual string strForPrint() = 0;
};

class HelpCommand : public Command
{
    COMMANDS commandHelp;
    std::unique_ptr<Arguments> args;
public:
    HelpCommand();
    HelpCommand(std::unique_ptr<Arguments>& givenArgs);
    HelpCommand(COMMANDS command);
    HelpCommand(COMMANDS command, const std::string& srcPath, const std::string& dstPath);
    HelpCommand(COMMANDS command, Arguments& args);

    void execute(RequestHandler* handler);
    string strForPrint();
    void validateArgs(){};
};

class InvalidCommand : public Command
{
    std::unique_ptr<Arguments> args;
public:
    InvalidCommand() = default;
    InvalidCommand(std::unique_ptr<Arguments>& givenArgs);
    virtual void execute(RequestHandler* handler);
    virtual string strForPrint();
    virtual void validateArgs();
   
};

class GetCommand : public Command
{
    COMMANDS commandGet;
    std::unique_ptr<Arguments> args;
public:
    GetCommand() = delete;
    GetCommand(const GetCommand&) = delete;

    GetCommand(std::unique_ptr<Arguments>& givenArgs);
    GetCommand(COMMANDS command, std::unique_ptr<Arguments>& givenArgs);
    virtual void execute(RequestHandler* handler);
    virtual string strForPrint();
    virtual void validateArgs();
    
    /**
     * Pre-conditions:
     * Post-conditions: returns local path
    */
    inline const string srcPath()
    {
        return string(args->at(0));
    };

    /**
     * Pre-conditions:
     * Post-conditions: returns dropbox's path
    */
    inline const string dstPath()
    {
        return string(args->at(1));
    };
};

class PutCommand : public Command
{
    COMMANDS commandPut;
    std::unique_ptr<Arguments> args;
public:
    PutCommand() = delete;
    PutCommand(std::unique_ptr<Arguments>& givenArgs);
    virtual void execute(RequestHandler* handler);
    virtual string strForPrint();
    virtual void validateArgs();
    
    /**
     * Pre-conditions:
     * Post-conditions: returns local path
    */
    inline const string srcPath()
    {
        return string(args->at(0));
    };

    /**
     * Pre-conditions:
     * Post-conditions: returns dropbox's path
    */
    inline const string dstPath()
    {
        return string(args->at(1));
    };
};
