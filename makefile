CC = gcc
CFLAGS = -g -std=c11 -D_POSIX_C_SOURCE=200809L -O2



INCLUDES = -IEval -ILexer -IParser -Itests -IError_handler -IData_structures -I.

SRCS = \
lox.c \
Data_structures/functionTable.c \
Data_structures/functionEnv.c \
Data_structures/Environment.c \
Data_structures/hashtable.c \
Data_structures/freeStuff.c \
Lexer/lexer.c \
Lexer/lexer_utils.c \
Lexer/utils.c \
Parser/parse_tree_def.c \
Parser/recursive_descent.c \
Parser/parser.c \
Eval/lib.c \
Eval/eval.c \
Error_handler/error_handler.c

TARGET = a

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

