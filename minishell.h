/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/06/19 19:46:19 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "struct.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
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

// ast utils
// void ft_build_ast_node()// ! TODO

int			main(int argc, char **argv, char **envp);

// libft TODO replace b the submodule

// tokenisation
t_cmd		*create_cmd_node(char *cmd, char *redir, char c);
char		**ft_strdup_array(char **cmd);
int			ft_str_is_alpha(char *s);
int			ft_is_symb(char *cmd, char *symb);
int			ft_quote_len(char *s, t_envp **env, int len);
int			ft_tokenize(char *buffer, save_struct *t_struct, t_envp **env);
int			ft_check_double_symbols(char *s, char **cmd);
int			ft_exec_syntax_functions(t_cmd **cmd, t_envp **env);
int			ft_init_ft_tab(int (*ft_tab[10])(t_cmd *));
int			ft_get_path(t_cmd *node);
int			ft_handle_quote(char *s, char **cmd, int len,
				save_struct *t_struct);
int			ft_putstr_cmd_fd(char *s, int fd, char **str, int flag);
void		ft_clean_cmd_lst(t_cmd **lst, save_struct *t_struct);
char		*ft_search_var(char *var, t_envp **env);

// Parsing
int			ft_var_len(char *s, int brace_flag);
void		ft_wildcard(t_cmd **cmd);

// lst_proto
void		ft_save_envp(char **envp_tab, t_envp **envp_lst);
int			ft_return_code(char *code, t_envp **env);
void		ft_create_token_lst(char *buffer, save_struct *t_struct);
void		add_to_lst(t_cmd **head, t_cmd *new_node);
void		add_to_envp_lst(t_envp **head, t_envp *new_node);
void		ft_remove_null_node(t_cmd **lst);
t_cmd		*lst_last(t_cmd *node);
t_envp		*lst_envp_last(t_envp *node);
void		ft_free_node(t_cmd *node);
t_envp		*create_envp_node(char *var_name);
void	ft_print_lst(t_cmd *node); // A SUPP A LA FIN
void		ft_free_tab(char **split);
void		ft_free_lst(t_cmd *lst);
void		ft_free_envp_lst(t_envp **lst);
void		ft_all_free(save_struct *t_struct);
int			ft_lst_size(t_cmd *cmd);
void		ft_print_env(t_envp **env);

// General utils
int			ft_safe_malloc(char **s, int size);
void		ft_override_content(char **s1, char *s2);
void		ft_swap_content(char **s1, char **s2);

// exec
void		ft_exec(save_struct *t_struct, char **envp);
int			ft_exec_single_cmd(save_struct *t_struct, char **envp);
void		ft_exec_multi_cmds(save_struct *t_struct, char **envp);
t_ast		*build_ast_recursive(t_cmd *start, t_cmd *end, t_ast *parent);
t_ast		*create_ast_node(t_cmd *node, t_ast *parent);
void		print_ast(t_ast *root, int depth, char prefix);
int			exec_ast_recursive(t_ast *root, char **envp, t_ast *save_root,
				int return_value, save_struct *t_struct);
int			ft_exec_tree(t_ast *root);
int			exec_leaf(t_ast *root, char **envp, t_ast *save_root,
				int return_value, save_struct *t_struct);
const char	*cmd_type_to_string(enum s_token_type type);
void	ft_parse_error(t_cmd *cmd);

	// BUILTINS
	int ft_dispatch_builtin(char **cmd, save_struct *t_struct);
int			ft_export(char **var, t_envp **env);
int			ft_unset(char **var, t_envp **env);
int			ft_env(t_envp **envp);
int			ft_echo(char **cmd, t_envp **env);
int			ft_exit(char **code, t_envp **env);
int			ft_print_envp(t_envp **envp);
int			ft_pwd(t_envp **envp);
int			ft_cd(char **cmd, save_struct *t_struct);

// Faire appel a la fonction ft_get_path avant ou pendant l execution,
// y rajouter une fonction pour la gestion d erreurs ?

#endif