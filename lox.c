#include "lox.h"

int main(int argc, char** argv)
{
    if(argc>1)
    {
        printf("Usage: ./jlox [script] ");
    }
    else if(argc==1)
    {
        runFile(argv[0]);
    }
    else
    {
        runPrompt();
    }
}