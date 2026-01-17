# Installation

To clone to local repo, run in terminal
``` bash
git clone https://github.com/RitabanChatterjee/LOX_interpreter/
```

# Usage

## Parser Usage
  To us the Parser add `#include "parser.h"` to the C file you want to use the parser in. 
   After this,run from project root:

 ``` bash
 gcc -o a <path_to_your_file>.c Lexer/lexer.c Lexer/lexer_util
s.c Lexer/utils.c Parser/parse_tree_def.c Parser/recursive_descent.c Parser/parser.c -ILexer -IParser
```
## Lexer Usage
   To use the lexer, add `#include "lexer.h"` to your C file , then run from project root
```bash
gcc -o a <path_to_your_file>.c Lexer/lexer.c Lexer/lexer_utils.c Lexer/utils.c
```
Note: Don't use the makefile yet, it isn't working correctly.

## REPL usage: To use the REPL for the language 

  ```bash
 gcc -o RClox -g lox.c Lexer/lexer.c Lexer/lexer_utils.c Lexer/utils.c Parser/parse_tree_def.c Parser/recursive_descent.c Parser/parser.c Eval/lib.c Eval/eval.c  Error_handler/error_handler.c -IEval -ILexer -IParser -Itests -IError_handler
```
then 
```bash
./RClox
```
At present, you cannot use assignment statements as resolving has not been done, not can you use if statements, classes, functions etc. Any expression however will be evaluated (except for AND and OR, those are pending (we dont have && or ||, and have the uppercase words instead) ).
After entering an expression, press enter to see its value. 

Truthiness rules are similar to python. 


