
#include "parser.h"
void testParser()
{
    printTree(parse("\"a\" * (b+c==d)",15));

}
int main()
{
    testParser();
}