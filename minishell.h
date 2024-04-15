/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/04/15 10:43:25 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_token
{
    char *token;
    int type;
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

#endif