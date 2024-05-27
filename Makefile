CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
CC = cc

PARSEDIR = parse
EXECDIR = exec 
LIBFTDIR = libft

PARSE_SRCS = $(wildcard $(PARSEDIR)/*.c)
EXEC_SRC = main.c \
exec/child.c \
exec/exec_parse.c \
exec/fork.c \
exec/ast_utils.c \

LIBFT = $(LIBFTDIR)/libft.a
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
EXEC_OBJ = $(EXEC_SRC:.c=.o)

NAME = minishell

$(LIBFT):
	@make -C $(LIBFTDIR)
	@echo "Libft compiled successfully"

$(NAME): $(PARSE_OBJS) $(EXEC_OBJ) | $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $(PARSE_OBJS) $(EXEC_OBJ) -L$(LIBFTDIR) -lft $(LDFLAGS)
	@echo "Compilation successful: $@"

all: $(NAME)

clean:
	@rm -f $(PARSE_OBJS) $(EXEC_OBJ)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re