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
    "\"hello\" + 1 != \"hello1\""
};


void evalTester()
{
    for(int i=0;i<52;i++)
    {
        Expr* ex=parse(exprTests[i],strlen(exprTests[i]));
        

        printTree(ex); printf(" : ");fflush(stdout);
        Literal l=eval(ex);
        printTree(new_literal(l.t,l.val));printf("   Testcase : %d",i);
        printf("\n");
    }
}

int main()
{
    evalTester();
}