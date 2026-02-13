#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "eval.h"
// Assume these exist in your codebase
Stmt parseStmt(char* src, int len);
void printStatementTree(Stmt s);

void testFunctionParsing(void)
{
    const char* tests[] = {
        "fun foo() { if(1==1) {return 1;} else if(2==2){return 2;} else if(3==3){return 3;}}",
        "fun add(a, b) { return   a + b; }",
        "fun square(x) { x * x; }",
       // "fun max(a, b) { if (a > b) { return a; } else { return b; } }",
        "fun factorial(n) { var a=1; { return 1; } return f(n,2*b+1) * n-1; }",
        "fun main() { var x = 10; var y = 20; return x+y; }",
        "var x=main();",
        "fun add(a,b){return a+b;}",
      
        "print add(10,309);",
            "fun foo() { return 42; }",
    "print foo();",                        // prints 42

    "fun add(a, b) { return a + b; }",
    "print add(10, 5);",                   // prints 15
        
    "fun square(x) { return x * x; }",
    "print square(7);",                    // prints 49

    "fun cube(x) { return x * x * x; }",
    "print cube(3);",                      // prints 27

    // nested function calls
    "fun double(x) { return add(x, x); }",
    "print double(21);",                   // prints 42

    "fun sum3(a, b, c) { return a + b + c; }",
    "print sum3(1, 2, 3);",                // prints 6

    "fun inc(x) { return x + 1; }",
    "print inc(99);",                      // prints 100

    // using other functions as arguments
    "fun times2plus1(x) { return add(mul(x,2),1); }",
    "print times2plus1(5);",               // prints 11 (if mul exists)
    
    // variables and calls
    "var x = square(5);",
    "print x;",                            // prints 25

    "var y = add(10, 15);",
    "print y;",                            // prints 25

    // function returning a call
    "fun magic(a, b) { return add(a, b); }",
    "print magic(7, 8);",                  // prints 15

    // "f(n*2+1,0+1)",
    // "vard(eori*ab,109)",

    };

    int ntests = sizeof(tests) / sizeof(tests[0]);

    envpack en;
    en.curr=initEnvironmentStack(512);
    en.fcurr=initFunctionStack(512);
    for (int i = 0; i < ntests; i++) {
        printf("==== Test %d ====\n    :%s", i,tests[i]);fflush(stdout);
       Stmt s=parseStmt(tests[i],strlen(tests[i]));
       printStatementTree(s);
        printf("\n\n");
    }
}

int main(void)
{
    testFunctionParsing();
    return 0;
}
