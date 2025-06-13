NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = \
    src/main.c \
    src/parse/atoi_utils.c \
    src/parse/free_utils.c \
    src/parse/parse_input.c \
    src/parse/parse_utils.c \
    src/parse/split.c \
    src/parse/string_utils.c \
    src/movements/operations_utils.c \
    src/movements/push_ops.c \
    src/movements/reverse_rotate_ops.c \
    src/movements/rotate_ops.c \
    src/movements/swap_ops.c \
    src/algorithm/assign_indexes.c \
    src/algorithm/chunk_sort.c \
    src/algorithm/sort.c \
    src/algorithm/sort_small.c \
    src/algorithm/stack_utils.c

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
