CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L



INCLUDES = -IEval -ILexer -IParser -Itests -IError_handler -IData_structures

SRCS = \
tests/evaltester.c \
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

