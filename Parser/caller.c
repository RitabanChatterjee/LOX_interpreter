
#include "parser.h"
char* testExpressions[] = {
    "\"a\" * (b + c == d)",            // strings, identifiers, parentheses
    "x + y * z",                        // precedence test
    "(x + y) * z",                      // grouping
    "a / (b - c) + 42",                 // combination of operators
    "-x + 3.14",                         // unary minus, float
    "true && false || nil",              // logical ops
    "!(a == b)",                         // unary logical not
    "x > y && y < z",                    // relational and logical
    "foo + bar * (baz - qux) / 2",       // nested operations
    "123 + 456 - 789",                   // integer arithmetic
    "\"hello\" + \"world\"",             // string concatenation (if supported)
    "a == b == c",                        // multiple equality
    "x + -y * z",                         // unary with binary
    "(a + b) * (c + d) / (e - f)",       // multiple groupings
    "g && (h || i) && !j"               // no && in this lang, expected output is g
};

void testParser()
{
    for(int i=0;i<15;i++)
    {
        printTree(parse(testExpressions[i],strlen(testExpressions[i])));
        printf("\n");
    }

}
int main()
{
    testParser();
}