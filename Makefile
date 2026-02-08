CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= push_swap

SRC		= main.c \
		  input_check.c input_check_utils.c \
		  initialization.c \
		  stack.c \
		  swap.c push.c rotate.c reverse_rotate.c \
		  sort_tiny.c sort.c \
		  position.c cost.c do_move.c \
		  utils.c

OBJ		= $(SRC:.c=.o)
libft	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
