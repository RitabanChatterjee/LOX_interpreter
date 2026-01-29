#include "lox.h"
void runPrompt() {
    char command[1024];
     Environment* curr=initEnvironmentStack(10);
    while (1) {
        printf(">> ");
        fflush(stdout);

        if (!fgets(command, sizeof(command), stdin)) {
            printf("\n");
            break; // EOF (Ctrl+D)
        }
        if(!strcmp(command,"exit\n")) break;
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n')
            command[len - 1] = '\0';

        Expr* ex = parse(command, strlen(command));
       
        Literal ans = eval(ex,curr);
        printTree(new_literal(ans.t, ans.val));
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    printf("%d",argc);
    if(argc>2)
    {
        printf("Usage: ./lox [script] ");
    }
    else if(argc==2)
    {
        //runFile(argv[0]);
        printf("This is running");
    }
    else
    {
        runPrompt();
    }
}