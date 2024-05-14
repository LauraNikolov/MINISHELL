/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:24:22 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/14 17:03:18 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

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
}					t_token_type;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	int				bool;
	int 			prev_fd;
	t_token_type	type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct ope {
    char *content;
    int prior;
} ope;

typedef struct commands {
    int std_in;
    int std_out;
    char *infile;
    char *outfile;
    char **cmds;
    char *cmd_path;
} commands;

typedef struct s_ast
{
	t_token_type	type;
	union data
    {
        struct ope operator;
        struct commands command;
    } data;
	struct s_ast	*right;
	struct s_ast	*left;
	struct s_ast    *parent;
}					t_ast;

typedef struct s_envp
{
	char			*var_path;
	char			*var_name;
	struct s_envp	*next;
}					t_envp;

typedef struct save_struct 
{
    struct s_cmd *cmd;
    struct s_ast *ast;
    struct s_envp *envp;
    struct s_all_struct *all_struct;
} save_struct;

#endif