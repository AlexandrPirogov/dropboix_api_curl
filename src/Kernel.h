#pragma once
#include "CommandsBuilder.h"
#include "curl/RequestHandler.h"
#include <fstream>

/**
 * Class to Facade two compose two classes: 1) Class to handle Requests 2) Class to handle terminal input
*/
class Kernel
{   
    std::unique_ptr<CommandsBuilder> commandsBuilder;
    std::unique_ptr<RequestHandler> requestHandler;
public:
    Kernel() = delete;

    /**
     * Pre-condition: given name of existsing file with user access code
     * Post-condition: created instance of Kerenl
    */
    Kernel(char*);

    /**
     * Pre-condition: given count of inputed words by user and words
     * Post-condition: inputed command will be executed
    */
    void executeCommand(int argc, char* argv[]);
};