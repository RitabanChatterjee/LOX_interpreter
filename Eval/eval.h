#ifndef EVAL_H
#define EVAL_H

#include "lib.h"
#include "error_handler.h"
#include"Environment.h"
Literal eval(Expr* expr, Environment* curr);
#endif