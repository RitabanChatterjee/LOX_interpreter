#include <stdio.h>
#include <string.h>
#include "Environment.h"

typedef struct {
    char* varname;
    char* val;
} testcase;

void bindVar(Environment* env, char* name, char* val)
{
    Literal v;
    v.t.tType = STRING;
    v.val.str = strdup(val);
    v.t.token_val.str = strdup(val);
    name=strdup(name);
    v.t.line = -1;
    v.t.lType = LIT_STRING;
    addToEnvironment(name, env, v);
}

void check(Environment* env, char* name, char* expect)
{
    Literal out;
    if (!expect) {
        if (getValue(name, env, &out))
            printf("❌ %-8s -> %s (expected not found)\n", name, out.val.str);
        else
            printf("✅ %-8s not found\n", name);
    } else {
        if (!getValue(name, env, &out))
            printf("❌ %-8s not found (expected %s)\n", name, expect);
        else if (strcmp(out.val.str, expect) != 0)
            printf("❌ %-8s -> %s (expected %s)\n", name, out.val.str, expect);
        else
            printf("✅ %-8s -> %s\n", name, out.val.str);
    }
}

int main()
{
    printf("\n==== TEST 1: Basic insert & lookup ====\n");
    Environment* g = initEnvironmentStack(4);
    bindVar(g, "a", "1");
    bindVar(g, "b", "2");
    check(g, "a", "1");
    check(g, "b", "2");
    check(g, "c", NULL);

    printf("\n==== TEST 2: Shadowing vs parent lookup ====\n");
    Environment* e1 = getNestedEnvironment(g, 4);
    bindVar(e1, "a", "10");  // shadow
    check(e1, "a", "10"); // local
    check(e1, "b", "2");  // from parent
    check(g,  "a", "1");  // unchanged

    printf("\n==== TEST 3: Deep nesting chain ====\n");
    Environment* e2 = getNestedEnvironment(e1, 4);
    Environment* e3 = getNestedEnvironment(e2, 4);
    bindVar(e3, "c", "30");
    check(e3, "c", "30");
    check(e3, "a", "10"); // from e1
    check(e3, "b", "2");  // from g
    check(e3, "x", NULL);

    printf("\n==== TEST 4: Sibling isolation ====\n");
    Environment* sib = getNestedEnvironment(g, 4);
    bindVar(sib, "d", "40");
    check(sib, "d", "40");
    check(e1,  "d", NULL);
    check(g,   "d", NULL);

    printf("\n==== TEST 5: Parent mutation after child creation ====\n");
    bindVar(g, "e", "50");
    check(e1, "e", "50");
    check(e3, "e", "50");

    printf("\n==== TEST 6: Child shadow does not leak upward ====\n");
    bindVar(e2, "b", "200");
    check(e2, "b", "200");
    check(e3, "b", "200");
    check(e1, "b", "2");
    check(g,  "b", "2");

    printf("\n==== TEST 7: Freeing deepest scope ====\n");
    freeEnvironment(e3);
    check(e2, "c", NULL);
    check(e2, "a", "10");
    check(e2, "b", "200");

    printf("\n==== TEST 8: Freeing middle scope ====\n");
    freeEnvironment(e2);
    check(e1, "b", "2");
    check(e1, "a", "10");
    check(e1, "c", NULL);

    printf("\n==== TEST 9: Freeing sibling scope ====\n");
    freeEnvironment(sib);
    check(g, "d", NULL);
    check(e1, "d", NULL);

    printf("\n==== TEST 10: Overwrite in same scope ====\n");
    bindVar(g, "a", "999");
    check(g,  "a", "999");
    check(e1, "a", "10"); // shadow still wins

    printf("\n==== TEST 11: Large chain lookup stress ====\n");
    Environment* cur = g;
    for (int i = 0; i < 50; i++) {
        cur = getNestedEnvironment(cur, 2);
        char* buf=(char*)malloc(16);
        sprintf(buf, "v%d", i);
        bindVar(cur, buf, "x");
    }
    check(cur, "a", "999");
    check(cur, "b", "2");
    check(cur, "v0", "x");
    check(cur, "v49", "x");
    check(cur, "nope", NULL);

    printf("\n==== TEST 12: Shadow chain collapse ====\n");
    Environment* s1 = getNestedEnvironment(g, 2);
    Environment* s2 = getNestedEnvironment(s1, 2);
    Environment* s3 = getNestedEnvironment(s2, 2);
    bindVar(g,  "x", "1");
    bindVar(s1, "x", "2");
    bindVar(s2, "x", "3");
    bindVar(s3, "x", "4");
    check(s3, "x", "4");
    freeEnvironment(s3);
    check(s2, "x", "3");
    freeEnvironment(s2);
    check(s1, "x", "2");
    freeEnvironment(s1);
    check(g,  "x", "1");

    printf("\n==== TEST 13: Stress overwrite + lookup ====\n");
    for (int i = 0; i < 1000; i++) {
        char buf[16];
        sprintf(buf, "k%d", i);
        bindVar(g, buf, "v");
    }
    for (int i = 0; i < 1000; i += 100) {
        char buf[16];
        sprintf(buf, "k%d", i);
        check(g, buf, "v");
    }

    freeEnvironment(e1);
    freeEnvironment(g);
}
