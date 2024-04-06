/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:41:19 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/04/06 17:34:20 by lauranicolo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>

enum node_type
{
    COMMAND,
    PIPE,
    AND,
    OR,
    REDIR, //plusieurs type de redirections a completer
}

typedef struct s_ast
{
    enum node_type type;
    char **args;
    struct s_ast *right;
    struct s_ast *left;
}                   t_ast;

//ast utils
void ft_build_ast_node()// ! TODO


#endif