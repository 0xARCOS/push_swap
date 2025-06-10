NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/parse/*.c $(SRC_DIR)/movements/*.c $(SRC_DIR)/algorithm/*.c)
OBJS := $(SRCS:.c=.o)

INC := -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
