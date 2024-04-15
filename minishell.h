/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/04/15 12:17:34 by renard           ###   ########.fr       */
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
    char *pipcell;
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

//libft TODO replace b the submodule
char	**ft_split_cmd(char *s, char *sep);
char	*ft_strjoin(char *s1, char *s2);


#endif