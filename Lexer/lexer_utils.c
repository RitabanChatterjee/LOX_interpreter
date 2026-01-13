#define ERROR_TOKEN (ScanResult) {-10,-10}
#include "lexer_utils.h"

int line=0;int length = 0; 
void addIdentifier(TokenType t1,LiteralType lt1,Value val,TokenList* list,char* id)
{
    Token nt;
    nt.tType=t1;
    nt.lType=lt1;
    nt.line=line;
    int len=strlen(id);
    id[len]='\0';
   nt.identifier_name=strdup(id);
    
    switch(nt.lType)
    {
        case LIT_STRING:
        nt.token_val.str=strdup(val.str);
        break;
        case LIT_INTEGER:
        nt.token_val.i=val.i;
        break;
        case LIT_FLOAT:
        nt.token_val.f=val.f;
        break;

    }
    addToken(nt,list);
}
void addTok(TokenType t1,LiteralType lt1,Value val,TokenList* list)
{
    Token nt;
    nt.tType=t1;
    nt.lType=lt1;
    nt.line=line;
   
    switch(nt.lType)
    {
        case LIT_STRING:
        nt.token_val.str=strdup(val.str);
        break;
        case LIT_INTEGER:
        nt.token_val.i=val.i;
        break;
        case LIT_FLOAT:
        nt.token_val.f=val.f;
        break;

    }
    addToken(nt,list);
}

static char advance(int* current, char* str)
{
    char b=str[*current];(*current)++;
    return b;
}

 static char peek(int* current , char* str)
{   if(*current==length) return '\0';
    char b=str[*current];
    return b;
}

static int isDigit(char c)
{
    return (c>='0' && c<='9');
}

static int isVar(char c)
{
    return (c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_';
}
static int isalphaNumeric(char c)
{
    return isVar(c) || isDigit(c);
}
/* handlers for strings, comments and numbers*/

//---------------------------------------------------------------------------------------------
static void handleString(int* current,char* str) //assumes str[*current]=='"'
{
  
    advance(current,str);
    char b;
    while ( (b = peek(current,str)) != '"' )
    {   if(b=='\0')
        {
            char error_msg[128];
            
        snprintf(error_msg, sizeof(error_msg),"Unterminated string on line %d", line);

            //report(error_msg,0); //in errors .h, 0 is lexer error.
            return ;
        }
        advance(current,str);
    }
    advance(current, str); // consume closing "

}

static void skipLine(int * current, char* str)
{
    while(peek(current,str)!='\0' && peek(current,str)!='\n')
    {
        advance(current,str);
    }
}

static LiteralType handleNumbers(int * current, char* str)
{
    LiteralType f=LIT_INTEGER;
    while(isDigit(peek(current,str)))
    {
        advance(current, str);
    }
    if(peek(current,str)=='.')
    {
        f=LIT_FLOAT;
        advance(current,str);
        while(isDigit(peek(current,str)))
        {
            advance(current, str);
        }
    }
    
    return f;
    
}

static TokenType handleIdentifier(int* current, char* str)
{
    while(isalphaNumeric(peek(current,str)))
    {
        advance(current,str);
    }
    return IDENTIFIER;
}
//----------------------------------------------------------------------------------------




 static ScanResult tokenAndLiteralTypeHelper(TokenType t1,LiteralType lt1)
{
    ScanResult sct;
    sct.l=lt1;
    sct.t=t1;
    return sct;
}
ScanResult scanToken(char* str, int* current)
{   
    char c=str[*current];
    (*current)++;
    switch (c)  
    {
      case '(': return tokenAndLiteralTypeHelper(LEFT_PAREN,LIT_NONE);break;
      case ')': return tokenAndLiteralTypeHelper(RIGHT_PAREN,LIT_NONE); break;
      case '{': return tokenAndLiteralTypeHelper(LEFT_BRACE, LIT_NONE); break;
      case '}': return tokenAndLiteralTypeHelper(RIGHT_BRACE,LIT_NONE); break;
      case ',': return tokenAndLiteralTypeHelper(COMMA,LIT_NONE); break;
      case '.': return tokenAndLiteralTypeHelper(DOT,LIT_NONE); break;
      case '-': return tokenAndLiteralTypeHelper(MINUS,LIT_NONE); break;
      case '+': return tokenAndLiteralTypeHelper(PLUS,LIT_NONE); break;
      case ';': return tokenAndLiteralTypeHelper(SEMICOLON,LIT_NONE); break;
      case '*': return tokenAndLiteralTypeHelper(STAR,LIT_NONE); break; 
      case '!' :
        if(peek(current,str)=='=')
        {(*current)++;return tokenAndLiteralTypeHelper(BANG_EQUAL,LIT_NONE);}
        else
        return tokenAndLiteralTypeHelper(BANG,LIT_NONE);
        break;
      case '=':
        if(peek(current,str)=='=')
            {   (*current)++;
                return tokenAndLiteralTypeHelper(EQUAL_EQUAL,LIT_NONE);
            }
        else
            return tokenAndLiteralTypeHelper(EQUAL,LIT_NONE);
            break;
        case '<':
            if(peek(current,str)=='=')
            {    (*current)++;
                return tokenAndLiteralTypeHelper(LESS_EQUAL,LIT_NONE);
            }
            else
            return tokenAndLiteralTypeHelper(LESS,LIT_NONE);
            break;
        case '>':
            if(peek(current,str)=='=')
            {(*current)++;return tokenAndLiteralTypeHelper(GREATER_EQUAL,LIT_NONE);}
            else
            return tokenAndLiteralTypeHelper(GREATER,LIT_NONE);
            break;
        case '"':
            handleString(current,str);
            return tokenAndLiteralTypeHelper(STRING,LIT_STRING);break;
        case '\n':
        line++;break;
        case ' ':
        break;
        case '\r':
        break;
        case '\t':
        break;
        case '/':
            if(peek(current,str)=='/')
            {
                skipLine(current,str);
            }
            else 
            {
                return tokenAndLiteralTypeHelper(SLASH,LIT_NONE);
            }
        break;

        default:
        if(isDigit(c))
        {
            LiteralType lt=handleNumbers(current,str);
            return tokenAndLiteralTypeHelper(NUMBER,lt);
        }
        else if(isVar(c))
        {
            TokenType t1=handleIdentifier(current,str);
            LiteralType lt1=LIT_NONE;
            return tokenAndLiteralTypeHelper(t1,lt1);
        }
        else
        {
            //report("Unexpected character",line);
        }
        break;

    }
    
    return ERROR_TOKEN;

}