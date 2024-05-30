/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/05/30 17:08:25 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "struct.h"
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
# include <dirent.h>
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

// ast utils
// void ft_build_ast_node()// ! TODO

int		main(int argc, char **argv, char **envp);

// libft TODO replace b the submodule

// tokenisation
t_cmd	*create_cmd_node(char *cmd, char *redir);
char	**ft_strdup_array(char **cmd);
int		ft_str_is_alpha(char *s);
int		ft_is_symb(char *cmd, char *symb);
int		ft_quote_len(char *s, t_envp **env);
int		ft_check_syntax(t_cmd *node);
int		ft_tokenize(char *buffer, save_struct *t_struct, t_envp **env);
int		ft_check_double_symbols(char *s, char **cmd);
void	ft_exec_syntax_functions(t_cmd **cmd, int (*ft_tab[9])(t_cmd *));
int		ft_init_ft_tab(int (*ft_tab[9])(t_cmd *));
int		ft_get_path(t_cmd *node);
int		ft_handle_quote(char *s, char **cmd, int len, save_struct *t_struct);
int		ft_check_brackets(t_cmd **cmd);
void	ft_putstr_cmd_fd(char *s, int fd, char *str);
void	ft_clean_cmd_lst(t_cmd **lst, save_struct *t_struct);
char	*ft_search_var(char *var, t_envp **env);

// Parsing
int		ft_check_braces(char *s);

// lst_proto
void	ft_save_envp(char **envp_tab, t_envp **envp_lst);
void	ft_create_token_lst(char *buffer, save_struct *t_struct);
void	add_to_lst(t_cmd **head, t_cmd *new_node);
void	add_to_envp_lst(t_envp **head, t_envp *new_node);
void	ft_remove_null_node(t_cmd **lst);
t_cmd	*lst_last(t_cmd *node);
t_envp	*lst_envp_last(t_envp *node);
void	ft_free_node(t_cmd *node);
t_envp	*create_envp_node(char *var_name, int flag);
void	ft_print_lst(t_cmd *node);   // A SUPP A LA FIN
void	ft_print_envp(t_envp *envp); // A SUPP A LA FIN
void	ft_free_tab(char **split);
void	ft_free_lst(t_cmd *lst);
void	ft_free_envp_lst(t_envp *lst);
void	ft_all_free(save_struct *t_struct);
int		ft_lst_size(t_cmd *cmd);
void	ft_print_env(t_envp **env);

// General utils
int		ft_safe_malloc(char **s, int size);

// exec
void	ft_build_ast(save_struct *t_struct, char **envp);
void	ft_exec(save_struct *t_struct, char **envp);
int		ft_exec_single_cmd(save_struct *t_struct, char **envp);

// BUILTINS
int		ft_export_cmd(t_envp **env, char **var);
void	ft_env(char **envp);
int		ft_echo(char **cmd);

// Faire appel a la fonction ft_get_path avant ou pendant l execution,
// y rajouter une fonction pour la gestion d erreurs ?

#endif