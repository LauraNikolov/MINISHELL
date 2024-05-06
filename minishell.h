/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/05/06 15:26:27 by lnicolof         ###   ########.fr       */
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
# include "struct.h"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

// ast utils
// void ft_build_ast_node()// ! TODO

int					main(int argc, char **argv, char **envp);

// libft TODO replace b the submodule

// tokenisation
char				**ft_strdup_array(char **cmd);
int					ft_str_is_alpha(char *s);
int					ft_is_symb(char *cmd, char *symb);
void				ft_split_cmd(t_cmd **lst);
char				*ft_quote(char *s);
int					ft_check_syntax(t_cmd *node);

// PARSE

// lst_proto
t_envp				*ft_save_envp(char **envp_tab, t_envp **envp_lst);
int					ft_create_token_lst(char *buffer, t_cmd **lst);
void				add_to_lst(t_cmd **head, t_cmd *new_node);
void				add_to_envp_lst(t_envp **head, t_envp *new_node);
t_cmd				*lst_last(t_cmd *node);
t_cmd				*create_cmd_node(char *cmd);
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