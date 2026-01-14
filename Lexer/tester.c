#include "lexer.h"
#include<stdlib.h>
static char* readFile(const char* filename, size_t* outLength) 
{
    FILE* file = fopen(filename, "rb");

    if (!file) {
        perror("fopen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length < 0) {
        fclose(file);
        return NULL;
    }

    char* buffer = malloc(length + 1); // +1 for null terminator
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0'; // null terminate
    fclose(file);

    if (outLength) *outLength = (size_t)length;
    return buffer;
}

// Test function
void testLexer(const char* filename) {
    size_t len;
    char* input = readFile(filename, &len);
    if (!input) {
        printf("Failed to read file: %s\n", filename);
        return;
    }

    TokenList tokens = scanTokens(input, (int)len);

    // Print all tokens using your printToken function
    for (int i = 0; i < tokens.size; i++) {
        Token t = tokens.tokens[i];
        printToken(t);
    }

    free(input);

    // Optional: free token strings if printToken doesn't do it
    // for (int i = 0; i < tokens.size; i++) {
    //     Token t = getToken(&tokens, i);
    //     if (t.lType == LIT_STRING) free(t.token_val.str);
    // }
}

// Example usage
int main() 
{
    testLexer("tester.txt");
    return 0;
}
