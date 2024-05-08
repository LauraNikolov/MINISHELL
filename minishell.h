/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/05/08 16:29:21 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef enum s_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
	O_BRACKET,
	C_BRACKET,
	NOT_FOUND,
}					t_token_type;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	int				bool;
	t_token_type	type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

typedef struct s_envp
{
	char			*var_path;
	char			*var_name;
	struct s_envp	*next;
}					t_envp;

// ast utils
// void ft_build_ast_node()// ! TODO

int					main(int argc, char **argv, char **envp);

// libft TODO replace b the submodule

// tokenisation
t_cmd				*create_cmd_node(char *cmd);
char				**ft_strdup_array(char **cmd);
int					ft_str_is_alpha(char *s);
int					ft_is_symb(char *cmd, char *symb);
char				*ft_quote(char *s);
int					ft_check_syntax(t_cmd *node);
int					ft_check_double_symbols(char *s, char **cmd);


// PARSE
int					ft_init_ft_tab(int (*ft_tab[9])(t_cmd *));
int					ft_get_path(t_cmd **lst);


// lst_proto
t_envp				*ft_save_envp(char **envp_tab, t_envp **envp_lst);
int					ft_create_token_lst(char *buffer, t_cmd **lst);
void				add_to_lst(t_cmd **head, t_cmd *new_node);
void				add_to_envp_lst(t_envp **head, t_envp *new_node);
void 				ft_remove_null_node(t_cmd **lst);
t_cmd				*lst_last(t_cmd *node);
void 				ft_free_node(t_cmd *node);
t_envp				*create_envp_node(char *var_name);
t_envp				*lst_envp_last(t_envp *node);
void				ft_print_lst(t_cmd *node);
void				ft_free_tab(char **split);
void				ft_free_lst(t_cmd *lst);
void				ft_free_envp_lst(t_envp *lst);

char				*ft_quote(char *s);

// Faire appel a la fonction ft_get_path avant ou pendant l execution,
// y rajouter une fonction pour la gestion d erreurs ?
int					ft_get_path(t_cmd **lst);

#endif