#include "Kernel.h"

Kernel::Kernel(char* tokenFile)
{
    
    requestHandler = std::make_unique<RequestHandler>(tokenFile);

    
    commandsBuilder = std::make_unique<CommandsBuilder>();

    
}

void Kernel::executeCommand(int argc, char* argv[])
{
    std::unique_ptr<Command> cmd = commandsBuilder->build(argv, argc);
    cmd->execute(requestHandler.get());
};