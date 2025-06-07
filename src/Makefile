# Variables
NAME = push_swap
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
INCLUDES = -I../include

SRC = \
main.c \
parse/parser.c \
parse/split.c \
parse/string_utils.c \
parse/free_utils.c \
parse/atoi_utils.c \
movements/operations.c \
algorithm/sort.c

OBJ = $(SRC:.c=.o)

# Reglas
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re