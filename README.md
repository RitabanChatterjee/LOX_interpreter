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



