#include "parser.h"
#include "eval.h"
char* tests[]=
{
    ";",
    "1;",
    "a;",
    "(a);",
    "((a));",

    // --- Variable declarations ---
    "var a;",
    "var a = 1;",
    "var a = b;",
    "var a = b = c;",
    "var a = b + c;",
    "var a = (b = c);",
    "var a = (b = c) + d;",
    "var a = b + (c = d);",

    // --- Assignment statements ---
    "a = 1;",
    "a = b;",
    "a = b = c;",
    "a = b = c = 10;",
    "a = b + c;",
    "a = b * c + d;",
    "a = (b + c) * d;",
    "a = (b = c);",
    "a = (b = c) + d;",
    "a = b + (c = d);",
    "(a = b);",
    "((a = b));",

    // --- Print statements ---
    "print 1;",
    "print a;",
    "print a = 1;",
    "print a = b = c;",
    "print (a = b);",
    "print (a = b) + c;",
    "print a + (b = c);",

    // --- Blocks ---
   

    // --- Nested blocks ---
    

    // --- Mixed declaration + assignment ---
    "var a; a = 1;",
    "var a = 1; a = 2;",
    "var a = b = c; a = a + 1;",
    "var a = (b = c); a = a * 2;",
    "var a; { var a = 2; } a = 3;",

    // --- Semicolon edge cases ---
    "var a;;",
    "a = 1;;",
    "print a;;",
    "{ var a;; a = 1;; }",

    // --- Should parse but error later (lvalue issues) ---
    "(a + b) = c;",
    "(a * b) = c;",
    "(a = b) = c;",
    "1 = a;",
    "(1 + 2) = 3;",

    // --- Precedence torture ---
    "a = b + c * d;",
    "a = (b + c) * d;",
    "a = b * c + d;",
    "a = b + (c * d);",
    "a = b + c * d + e;",
    "a = b * c + d * e;",
    "a = (b = c) * d;",
    "a = b + (c = d * e);",

    // --- Deep nesting ---
    "a = (((((b)))));",
    "a = (b = (c = (d = (e = f))));",
    "{ var a = (b = (c = (d = e))); print a; }",

    // --- Weird but legal ---
    "print (a = (b = (c = d)));",
    

    // --- Token adjacency / spacing ---
    "var a=1;",
    "a=b;",
    "a=b=c;",
    "print(a=b);",

    // --- Stress long chains ---
    "a=b=c=d=e=f=g;",
    "var a=b=c=d=e=f;",

};
void testStatementParser()
{
   // StmtArray statements=StmtArray_make();
   char* stmts[] =
    {"var x;",
"print x;",
"x = 1;",
"print x;",
    "{}",                                // empty block
    "{ var a = 1; }",                    // single statement
    "{ var a = 1; print a; }",           // multiple statements
    "{ { var a = 1; } }",                // nested block
    "{ print 1 + 2 * 3; var b = 4; }",    // mixed statements
    "{ var a = 1; { var b = 2; } print a; }", // nested inside
    "{",                                 // error: missing }
    "{ var a = 1; print a }",            // error: missing ;

"var y = 2;",
"print y;",

"var z;",
"z = x + y * 3;",
"print z;",

"var a = (x + y) * (z - 4) / 2;",
"print a;",

"var b;",
"b = -a + +z;",
"print b;",

"var c = b == a;",
"print c;",

"var d = b != a;",
"print d;",

"var e = (b > a) && (z <= 7);",
"print e;",

"var f = (b < a) || (z >= 6);",
"print f;",

"var g = !f;",
"print g;",

"var h;",
"h = x = y = z = 10;",
"print h; print x; print y; print z;",

"var i = h + x + y + z;",
"print i;",

"var j = \"hello\";",
"print j;",

"var k;",
"k = j + \" world\";",
"print k;",

"var l = \"num=\" + i;",
"print l;",

"var m = (x + (y * (z + (a - (b / 2)))));",
"print m;",

"var n = ((((((42))))));",
"print n;",

"var o = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10;",
"print o;",

"var p = 1 * 2 + 3 * 4 - 5 / (6 - 7 + 8);",
"print p;",

"var q = (1 + 2) * (3 + 4) / (5 - 6 + 7);",
"print q;",

"var r = -(-(-(-5)));",
"print r;",

"var s = !!(1 == 1);",
"print s;",

"var t = x == y == z;",
"print t;",

"var u = x < y < z;",
"print u;",

"var v;",
"v = (x = 3) + (y = 4) + (z = 5);",
"print v; print x; print y; print z;",

"x = x + 1;",
"print x;",
"y = y + 2;",
"print y;",
"z = z + 3;",
"print z;",

"((((((((((((x))))))))))));",
"print x;",

"var w;",
"w = \"\";",
"print w;",
"w = w + x + y + z;",
"print w;",

"var aa;",
"aa = aa = aa = 5;",
"print aa;",

"var bb = (aa = 2) + (aa = 3) * (aa = 4);",
"print bb; print aa;",

"var cc;",
"cc = (1 + 2) * (3 + 4) == 21;",
"print cc;",

"var dd;",
"dd = !(cc && false || true && !false);",
"print dd;",

"var ee;",
"ee = 1 < 2 && 3 < 4 || 5 < 6;",
"print ee;",

"var ff;",
"ff = (1 < 2) < 3;",
"print ff;",

"var gg;",
"gg = (x == 3) == true;",
"print gg;",

"var hh;",
"hh = (x = (y = (z = 7)));",
"print hh; print x; print y; print z;",

"var ii;",
"ii = x + (y = z + (a = b = 9));",
"print ii; print a; print b; print y;",

"var jj;",
"jj = \"a\" + \"b\" + \"c\" + 1 + 2 + 3;",
"print jj;",

"var kk;",
"kk = 1 + 2 + \"3\" + 4 + 5;",
"print kk;",

"var ll;",
"ll = \"(\" + (1 + 2) + \")\";",
"print ll;",

"var mm;",
"mm = !\"\";",
"print mm;",

"var nn;",
"nn = !!0;",
"print nn;",

"var oo;",
"oo = !!!true;",
"print oo;",

"var pp;",
"pp = - - - - 5;",
"print pp;",

"var rr;",
"rr = (x = 1, y = 2, z = 3);",
"print rr; print x; print y; print z;",

"var ss;",
"ss = (x = 1) + (y = 2) + (z = 3);",
"print ss; print x; print y; print z;",

"var tt;",
"tt = x == (y = 2) + 1;",
"print tt; print y;",

"var uu;",
"uu = (x = y) == z;",
"print uu; print x;",

// ---- intentional parse errors ----
"var vv;",
"vv = ((x)));",
"print vv;",

"var ww;",
"ww = ;",
"print ww;",

"var xx;",
"xx = 1 + * 2;",
"print xx;",

"var yy;",
"yy = ((1 + 2);",
"print yy;",

"var zz;",
"zz = \"unterminated string"


    }
;

int stmt_count = sizeof(stmts) / sizeof(stmts[0]);

Environment* env = initEnvironmentStack(512);

for (int i = 0; i < stmt_count; i++) {
    printf("=== TEST %d ===\n%s\n", i, stmts[i]);
    
    Stmt s = parseStmt(stmts[i], strlen(stmts[i]));
    if (s.type==STMT_ERROR) {
        printf("Parse failed\n\n");
        continue;
    }
    evalStmt(s, env);
    printf("\n");
}

}
int main()
{
    testStatementParser();
}