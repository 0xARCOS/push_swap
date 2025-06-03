# Variables
NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c parser.c utils.c
OBJ = $(SRC:.c=.o)

# Reglas
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re