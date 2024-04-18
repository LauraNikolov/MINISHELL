CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

PARSEDIR = parse
EXECDIR = exec 
LIBFTDIR = libft

PARSE = $(PARSEDIR)/ft_free_split.c \
		$(PARSEDIR)/lst_utils.c \
		main.c \

LIBFT = $(LIBFTDIR)/libft.a

OBJ = $(PARSE:.c=.o)

NAME = minishell

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBFTDIR) -lft
	@echo "Compilation successful: $@"

$(LIBFT):
	@make -C $(LIBFTDIR)
	@echo "Libft compiled successfully"

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
