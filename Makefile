NAME = push_swap
CHECKER = checker
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR := src
SRCS := $(filter-out $(SRC_DIR)/checker_main.c, $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/parse/*.c $(SRC_DIR)/movements/*.c $(SRC_DIR)/algorithm/*.c))
OBJS := $(SRCS:.c=.o)

CHECKER_SRCS := $(SRC_DIR)/checker_main.c $(wildcard $(SRC_DIR)/parse/*.c) \
    $(SRC_DIR)/algorithm/sort.c $(SRC_DIR)/movements/operations.c \
    $(SRC_DIR)/movements/operations_utils.c
CHECKER_OBJS := $(CHECKER_SRCS:.c=.o)

INC := -Iinclude

all: $(NAME) $(CHECKER)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(CHECKER): $(CHECKER_OBJS)
	$(CC) $(CFLAGS) $(CHECKER_OBJS) -o $(CHECKER)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(CHECKER_OBJS)

fclean: clean
	rm -f $(NAME) $(CHECKER)

re: fclean all

.PHONY: all clean fclean re
