#ifndef TOKENDEF_H
#define TOKENDEF_H
#include<stdlib.h>
#include <string.h>

typedef enum TokenType
{
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,token_EOF,MOD,
LIST, INDEX,PLUS_PLUS,MINUS_MINUS,PLUS_EQUAL,MINUS_EQUAL,STAR_EQUAL,SLASH_EQUAL,MOD_EQUAL
}TokenType;

typedef enum LiteralType
{
    LIT_NONE, LIT_STRING,LIT_INTEGER, LIT_FLOAT
}LiteralType;

 typedef union val
    {
        int i;
        float f;
        char* str;
    }Value;
typedef struct Token
{
    TokenType tType;
    LiteralType lType;
    Value token_val;
    int line;
    char * identifier_name;

}Token;
 

#endif