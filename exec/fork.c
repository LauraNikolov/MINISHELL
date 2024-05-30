/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/30 15:27:57 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_exec_tree(t_ast *root)
{
    int i;
    i = 0;
    
    (void)root;
    printf("CECI EST LE ROOT : \n");
    print_ast(root, 0 ,' ');
    return(i);
}

void set_exec_struct(save_struct *t_struct, char **envp)
{
    t_struct->exec->return_value = 0;
    t_struct->exec->prev_fd = 0;
    t_struct->exec->envp = envp;
    t_struct->exec->pipe = {0, 0};
}

void ft_exec_multi_cmds(save_struct *t_struct, char **envp)
{
    t_cmd *start; 
    t_cmd *end;

    set_
    start = t_struct->cmd;
    while(t_struct->cmd->next)
        t_struct->cmd = t_struct->cmd->next;
    end = t_struct->cmd;
    t_struct->cmd = start;
    t_struct->ast = build_ast_recursive(start, end);
    print_ast(t_struct->ast, 0, ' ');
    exec_ast_recursive(t_struct->ast, t_struct->exec);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
}
