#include "utils.h"
#include<stdio.h>
TokenList makeList()
{
    TokenList list;
    list.size=0;
    list.capacity=25;
    list.tokens=(Token*)(malloc(25*sizeof(Token)));
    return list;
}
void freeList(TokenList* list)
{
    free(list->tokens);
    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0;
}

void addToken(Token t, TokenList* list)
{
    if(list->size<list->capacity)
    {
        list->tokens[list->size]=t;
        list->size++;
    }
    else
    {
        list->capacity=2*list->capacity;
        list->tokens=(Token*)(realloc(list->tokens,list->capacity*sizeof(Token)));
        list->tokens[list->size]=t;
        list->size++;
    }
}

char* substring(const char *source, size_t start, size_t length) 
{
    // 1. Validate input indices (optional but good practice)
    if(length==0)
    {
         char* str=malloc(sizeof(char));str[0]='\0'; return str;
    }
    size_t source_len = strlen(source);
    if (start >= source_len) 
    {
         // Invalid start index
         char* str=malloc(sizeof(char));str[0]='\0'; return str;
    }
    // Adjust length if it exceeds the remaining string
    if (start + length > source_len) {
        length = source_len - start;
    }

    // 2. Allocate memory for the new substring
    // Add 1 byte for the null terminator ('\0')
    char *destination = (char *)malloc(length + 1);
    if (destination == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // 3. Copy the characters using memcpy (or strncpy)
    // source + start points to the starting character of the substring
    memcpy(destination, source + start, length);

    // 4. Manually add the null terminator
    destination[length] = '\0';

    return destination;
}
static const char *TokenTypeNames[] =
{
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

    "BANG", "BANG_EQUAL",
    "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",

    "IDENTIFIER", "STRING", "NUMBER",

    "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR",
    "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",

    "EOF"
};

void printToken(Token t)
{
    printf("Token Line: %d \tToken Token_Type: %s\t",t.line,TokenTypeNames[t.tType]);
    
   switch(t.lType)
   {
        case LIT_STRING:
        printf("Literal_value: %s\n",t.token_val.str);break;
        case LIT_INTEGER:
        printf("Literal_value: %d\n",t.token_val.i);break;
        case LIT_FLOAT:
        printf("Literal_value: %f\n",t.token_val.f);break;
        case LIT_NONE:
            if(t.tType==IDENTIFIER)
            {
                printf("Identifier_name %s\n",t.identifier_name);
            }
            else
                printf("Literal_value : None\n");
        break;
        
   }
}