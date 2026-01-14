CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -g 
TARGET  := a

SRC := \
    Parser/caller.c \
    Parser/parser.c \
    Parser/parse_tree_def.c \
    Parser/recursive_descent.c \
    Lexer/lexer.c \
    Lexer/lexer_utils.c \
    Lexer/utils.c

OBJ := $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

