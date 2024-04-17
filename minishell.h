/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/04/17 13:57:40 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <string.h>

typedef struct s_token
{
    char *cmd;
    char *options;
    char *envp_path;
    char *pipcell;
   // int envp_flag; // est ce que le binaire est dans une variable d environnement ?
    struct s_token *next;
}   t_token;

enum node_type
{
    COMMAND,
    PIPE,
    AND,
    OR,
    REDIR, //plusieurs type de redirections a completer
} ;

typedef struct s_ast
{
    enum node_type type;
    char **args;
    struct s_ast *right;
    struct s_ast *left;
}   t_ast;

//ast utils
//void ft_build_ast_node()// ! TODO

// Prompt utils
void ft_display_prompt(void);
int main(int argc, char **argv, char **envp);

//libft TODO replace b the submodule
char	**ft_split_cmd(char *s, char *sep);
char	*ft_strjoin(char *s1, char *s2);
t_token *create_node(char *cmd, char *envp_path);

// lst_proto

void add_to_lst(t_token **head, t_token *new_node);
t_token *lst_last(t_token *node);
void ft_free_split(char **split);


#endif