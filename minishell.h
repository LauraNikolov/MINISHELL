/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/05/31 14:27:47 by lauranicolo      ###   ########.fr       */
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
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "struct.h"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"


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
int					ft_get_path(t_cmd *node);


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
void				ft_all_free(save_struct *t_struct);
int 				ft_lst_size(t_cmd *cmd);

char				*ft_quote(char *s);


//exec
//void ft_build_ast(save_struct *t_struct, char **envp);
void ft_exec(save_struct *t_struct, char **envp);
int ft_exec_single_cmd(save_struct *t_struct, char **envp);
void ft_exec_multi_cmds(save_struct *t_struct, char **envp);
t_ast *build_ast_recursive(t_cmd *start, t_cmd *end);
t_ast *create_ast_node(t_cmd *node);
void print_ast(t_ast *root, int depth, char prefix);
int exec_ast_recursive(t_ast *root, char **envp, t_exec *exec);
int ft_exec_tree(t_ast *root);
int exec_leaf(t_ast *root, char **envp, t_exec *exec);

// Faire appel a la fonction ft_get_path avant ou pendant l execution,
// y rajouter une fonction pour la gestion d erreurs ?

#endif