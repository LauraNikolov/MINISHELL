CFLAGS = -Wall -Wextra -Werror -g3

SRC = main.c /

# LIBFT = libft/libft.a
		
OBJ = $(SRC:.c=.o) $(LIBFT)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	
$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 