#ifndef PARSER_H
#define PARSER_H

#include "recursive_descent.h"
#include "parse_tree_def.h"
#include "lexer.h"
Expr* parse(char* str,int len);
Stmt parseStmt(char* st,int len);
#endif /*PARSER_H*/