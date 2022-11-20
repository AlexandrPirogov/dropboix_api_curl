#include <iostream>
#include <string>
#include "Kernel.h"


int main(int argc, char* argv[])
{
    Kernel k(argv[1]);
    k.executeCommand(argc, argv);
}