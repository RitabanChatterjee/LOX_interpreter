#include "eval.h"
#include "Environment.h"
char* exprTests[] = {
    // Arithmetic
    "1 + 2 + 3",
    "4 * 5 - 6",
    "10 - 2 / 2",
    "2 + 3 * 4 - 5",
    "1.5 + 2.5 + 3.0",
    "2.0 * 3.0 * 4.0",
    "10.0 / 2.0 / 5.0",
    "(12+1)*(12-1)",
    // Unary !
    "!0",
    "!42",
    "!3.14",
    "!0.0",
    "!\"\"",
    "!\"hello\"",
    "!nil",

    // String concatenation
    "\"hello\" + \" \" + \"world\"",
    "\"foo\" + \"bar\"",
    "\"a\" + \"b\" + \"c\"",
    "\"123\" + 456",
    "\"pi:\" + 3.14",

    // Mixed unary ! + arithmetic
    "!0 + 1",
    "!42 + 2",
    "!3.14 + 2.0",
    "!\"\" + 1",
    "!nil + 3",

    // Comparisons numbers
    "1 == 1",
    "1 == 2",
    "2 != 3",
    "5 > 3",
    "2 < 4",
    "6 >= 6",
    "7 <= 8",
    "10 >= 5",
    "2 <= 1",

    // Comparisons floats
    "3.14 > 2.71",
    "2.71 < 3.14",
    "1.0 == 1.0",
    "2.0 != 3.0",
    "0.0 >= 0.0",
    "0.0 <= 0.1",

    // Comparisons strings
    "\"a\" == \"a\"",
    "\"a\" != \"b\"",
    "\"abc\" > \"ab\"",
    "\"ab\" < \"abc\"",
    "\"abc\" >= \"abc\"",
    "\"abc\" <= \"abcd\"",
    "(12+1)*(12-1)"
    // Mixed complex
    "!0 + 1 >= 1",
    "(!\"\" + 2) == 2",
    "1 + 2 * 3 > 5",
    "\"x\" + \"y\" == \"xy\"",
    "(!0 + 3.0) <= 4.0",
    "5 + !0 <= 6",
    "\"hello\" + 1 != \"hello1\"",
        "true and true",
    "true and false",
    "false and true",
    "false and false",

    "true or true",
    "true or false",
    "false or true",
    "false or false",

    "1 and 2",
    "0 and 5",
    "\"hi\" and \"bye\"",
    "\"\" and 3",

    "1 or 2",
    "0 or 5",
    "\"\" or \"hello\"",

    "1 < 2 and 3 < 4",
    "1 < 2 and 3 > 4",
    "1 > 2 or 3 < 4",
    "1 > 2 or 3 > 4",

    "1 + 2 * 3 and 7 == 7",
    "1 + 2 * 3 and 6 == 7",
    "10 - 5 > 3 or 2 == 3",

    "true or false and false",
    "false or true and false",
    "(true or false) and false",
    "true and false or true",
    "(true and false) or true",

    "1 < 2 and 3 < 4 or 0",
    "1 < 2 or 3 < 4 and 0",
    "(1 < 2 or 3 < 4) and 0",

    "false and (1 / 0)",
    "true or (1 / 0)",
    "false or (1 / 0)",
    "true and (1 / 0)",

    "!(true and false)",
    "!true or false",
    "!(true or false) and true",

    "nil or true",
    "nil and true",
    "nil or false",
    "nil and false",
    "false and (1 / 0)",
    "true or (1 / 0)",
    "false or (1 / 0)",
    "true and (1 / 0)",

    // --- Deep nesting short-circuit ---
    "false and (true or (false and (1 / 0)))",
    "true or (false and (true or (1 / 0)))",
    "(false and true) or (false and (1 / 0))",
    "(true or false) and (false or (1 / 0))",

    // --- Truthiness coercion extremes ---
    "0 and 1",
    "1 and 0",
    "\"\" and 1",
    "\"a\" and 0",
    "nil and true",
    "nil or true",
    "true and nil",
    "false or nil",

    // --- Unary + logical interaction ---
    "!true and true",
    "!false and false",
    "!(true and false)",
    "!(false or false)",
    "!0 and 1",
    "!\"\" or false",

    // --- Precedence traps ---
    "true or false and false",
    "false and true or true",
    "!true or true and false",
    "!(true or false) and true",

    // --- Mixed arithmetic + logical ---
    "(1 + 2) and (3 - 3)",
    "(1 + 2) or (3 - 3)",
    "(0 * 5) or (10 / 2)",
    "(10 / 2) and (0 * 5)",

    // --- Comparison + logical ---
    "(1 < 2) and (2 < 1)",
    "(1 < 2) or (2 < 1)",
    "(3 == 3) and (4 != 4)",
    "(3 == 4) or (4 != 4)",

    // --- Nested coercion + grouping ---
    "((1 and 2) and 0) or 3",
    "(1 and (2 or 0)) and 3",
    "((nil or 0) and \"\") or true",
    "(\"\" or nil) and (1 / 0)",

    // --- String truthiness edges ---
    "\"\" or \"x\"",
    "\"x\" and \"\"",
    "\"x\" or \"\"",
    "\"\" and \"x\"",

    // --- Nil dominance ---
    "nil and nil",
    "nil or nil",
    "(nil or false) and true",
    "(nil and true) or false",

    // --- Stress associativity ---
    "true and true and false and true",
    "false or false or true or false",
    "true or false or false and false",
    "false and true and true or true",

    // --- Evil nesting ---
    "true or (false and (true or (false and (true or (1 / 0)))))",
    "false and (true or (false and (true or (false and (1 / 0)))))",
   
    "a = 1",
    "b = 2",
    "c = a = 3",
    "d = b = a = 4",

    "x = 10",
    "x = x + 1",
    "x = x * 2",
    "x = x - 5",
    "x = x / 17",

    "a = 1 + 2 * 3",
    "b = (1 + 2) * 3",
    "c = 10 - 2 - 3",
    "d = 10 - (2 - 3)",

    "a = b = 1 + 2",
    "x = y = z = 5 * 2",
    "m = n = (2 + 3) * 4",

    "a = 10",
    "a = a",
    "a = a + a",
    "a = a = a = 7",

    "x = 1",
    "y = 2",
    "z = x = y = 3",
    "x = x + y",

    "s = \"hi\"",
    "s = s + \"!\"",
    "t = s",
    "u = t + \" world\"",

    "a = 10",
    "b = a + \"1\"",
    "a = b",

    "a=b=c=d=e=f=g=h=i=j=1",
    "a=a+1",
    "b=a+1",
    "c=b+1",
    "d=c+1",

    "x = (((((1)))))",
    "x = (1 + (2 * (3 + 4)))",

    "a = b = c = 10 + 5",
    "a = (b = (c = 20))",

    "x = (y = 5) + 1",
    "z = (a = 3) * (b = 4)",

    "a = 10",
    "a = \"hi\"",
    "a = a + \"!\"",

    "x = 1",
    "x = 2",
    "x = 3",
    "x = 4",
    "x = 5",

    /* === invalid (should error) === */
    "1 = a",
    "(a + b) = c",
    "\"x\" = 3",
    "true = false",
    "nil = 2",
    "a + b = c",
    "(a = b) = c",
    "a = b + c = d",
    "a = b or c = d",
    "a = !b = c",
    "a = 1",
"b = 2",
"c = a",
"d = b + c",
"e = 1 + 2 * 3",
"f = (1 + 2) * 3",

"a = b = 3",
"c = d = e = 4",
"x = y = z = 5 * 2",
"m = n = (2 + 3) * 4",
"a = (b = 5)",
"x = (y = (z = 10))",

"a = a + 1",
"a = a * 2",
"a = a - 3",
"a = a / 2",
"a = a + a",
"a = a * a",
"a = (a + a) * a",

"x = (y = 5) + 1",
"z = (a = 3) * (b = 4)",
"p = (q = 1) + (r = 2)",
"s = (t = u = 4) + 1",
"v = w = (x = y = 6)",

"a = b = c = 10 + 5",
"a = (b = (c = 20))",
"x = (y = 5) + (z = 6)",
"a = b + (c = 4)",
"a = (b = 2) + c",
"a = (b = 2) * (c = 3)",

"a = b = c = d = e = 1",
"a = a = a = 7",
"x = y = z = x + 1",

"1 = a",
"(a + b) = c",
"\"x\" = 3",
"true = false",
"nil = 2",
"(a = b) = c",
"a = b + c = d",
"a = b or c = d",
"a = !b = c",
"(a + b + c) = d",
"(a * b) = c",
"(true and false) = x",
"(nil or true) = y",
"a=1",
"a =1",
"a= 1",
"a=1+2*3",
"a = (b = c = d = 5)",
"a = (((b))) = 3",
"a = ((b = 3))",
"a = b = c + d = e",
"a = (b + c = d)",
"a = (b = c) = d",
"a = (b = (c = (d = 4)))",
"a = (b = 1) + (c = (d = 2) + 3)",
"a = (b = (c = 2) + 3)",
"a = ((b = 2) + 3) = 4",
"(a = b) + c = d",
"a = b = (c = d = e = f)",
"a = (b = c = d) + e",
"a = ((b)) = 3",
"(a) = 3",



};



void evalTester()
{
    Environment* curr=initEnvironmentStack(10);
    for(int i=0;i<sizeof(exprTests)/sizeof(exprTests[0]);i++)
    {
        //if(i!=72) continue;
        Expr* ex=parse(exprTests[i],strlen(exprTests[i]));
        

        printf("%s",exprTests[i]); printf(" : ");fflush(stdout);
        
        Literal l=eval(ex,curr);
        printTree(new_literal(l.t,l.val));printf("   Testcase : %d",i);
        printf("\n");
    }
}
void parseTester()
{
    char* tests[] = {
    // Basic assignment
    "a = 1;",
    "x = 42;",
    "foo = bar;",

    // Assignment returns value (chaining)
    "a = b = c = 10;",
    "x = y = 1 + 2 * 3;",
    "a = (b = 3);",

    // Precedence vs logicals
    "a = b or c;",
    "a = b and c;",
    "a = b or c = d;",        // should parse as a = (b or (c = d))
    "a = b = c or d;",        // a = (b = (c or d))

    // Precedence vs comparisons
    "a = b == c;",
    "a = b != c;",
    "a = b < c;",
    "a = b < c == d;",        // a = ((b < c) == d)

    // Precedence vs arithmetic
    "a = b + c * d;",
    "a = b * c + d;",
    "a = b + c = d;",         // INVALID (lvalue check)

    // Parentheses
    "(a) = 3;",               // INVALID
    "a = (b + c);",
    "a = (b = c) + d;",

    // Nested assignments in expressions
    "print a = 3;",
    "print a = b = 4;",
    "a = (b = (c = 5));",

    // Statement sequences
    "a = 1; b = 2; c = a = b;",
    "{ a = 1; b = a = 2; }",

    // Invalid targets
    "1 = a;",
    "\"x\" = 3;",
    "true = false;",
    "nil = 2;",
    "a + b = c;",
    "a * b = c;",

    // Missing RHS
    // "a = ;",
    // "a =",
    // "= 3;",

    // Edge associativity
    "a = b = c;",
    "a = (b = c);",
    "(a = b) = c;",           // INVALID

    // With unary
    "a = !b;",
    "a = -b;",                // if unary minus exists
    "a = !b = c;",            // INVALID

    // With logical short-circuit
    "a = b and c = d;",       // a = (b and (c = d))
    "a = b or c = d;",        // a = (b or (c = d))

    
};
    for(int i=0;i<sizeof(tests)/sizeof(tests[0]);i++)
    {   
        printf("%s  : ",tests[i]);
        Expr* ex=parse(tests[i],strlen(tests[i]));
        printTree(ex);
        printf("\n");
    }

}
int main()
{   
    evalTester();
   // parseTester();
}