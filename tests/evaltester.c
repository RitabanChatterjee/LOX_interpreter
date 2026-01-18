#include "eval.h"

char* exprTests[] = {
    // Arithmetic
    "1 + 2 + 3",
    "4 * 5 - 6",
    "10 - 2 / 2",
    "2 + 3 * 4 - 5",
    "1.5 + 2.5 + 3.0",
    "2.0 * 3.0 * 4.0",
    "10.0 / 2.0 / 5.0",

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


};


void evalTester()
{
    for(int i=0;i<sizeof(exprTests)/sizeof(exprTests[0]);i++)
    {
        //if(i!=72) continue;
        Expr* ex=parse(exprTests[i],strlen(exprTests[i]));
        

        printf("%s",exprTests[i]); printf(" : ");fflush(stdout);
        Literal l=eval(ex);
        printTree(new_literal(l.t,l.val));printf("   Testcase : %d",i);
        printf("\n");
    }
}

int main()
{
    evalTester();
}