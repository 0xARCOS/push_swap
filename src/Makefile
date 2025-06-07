# Variables
NAME = push_swap
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
INCLUDES = -I../include

SRC = \
main.c \
parser.c \
operations.c \
split.c \
string_utils.c \
free_utils.c \
atoi_utils.c

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