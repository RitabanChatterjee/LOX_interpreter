#include "lox.h"
void runPrompt() {
    char command[1024];
     Environment* curr=initEnvironmentStack(10);
     functionEnv* fcurr=initFunctionStack(512);
     envpack en;
     en.curr=curr;
     en.fcurr=fcurr;
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

        Stmt ex = parseStmt(command, strlen(command));
       
         evalStmt(ex,&en);
       // printTree(new_literal(ans.t, ans.val));
        printf("\n");
    }
}
void runFile(char* fname)
{
    FILE* f = fopen(fname, "rb");
    if (!f) {
        perror("File open failed");
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buff = malloc(size + 1);
    if (!buff) {
        perror("Memory allocation failed");
        fclose(f);
        return;
    }

    fread(buff, 1, size, f);
    buff[size] = '\0';   // ← THIS is important

    fclose(f);

    Value fg; 
    fg.i = 0;

    TokenList tokens = scanTokens(buff, size);
  //  addTok(token_EOF, LIT_NONE, fg, &tokens);

    Parser p;
    p.tokens = tokens;
    p.pointer = 0;
    envpack en;
    Environment* curr=initEnvironmentStack(10);
    functionEnv* fcurr=initFunctionStack(512);
    en.curr=curr;
    en.fcurr=fcurr;

    while (p.pointer<tokens.size)
    {
        Stmt s=declaration(&p);
        evalStmt(s,&en);
    }

    free(buff);
}
int main(int argc, char** argv)
{
 //   printf("%d",argc);
    if(argc>2)
    {
        printf("Usage: ./lox [script] ");
    }
    else if(argc==2)
    {
        runFile(argv[1]);
      //  printf("This is running");
    }
    else
    {
        runPrompt();
    }
}