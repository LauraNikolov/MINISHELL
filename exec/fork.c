/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/04 13:08:56 by lauranicolo      ###   ########.fr       */
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

void set_exec_struct(t_exec *exec)
{
    exec = (t_exec *)malloc(sizeof(t_exec));
    if(exec == NULL)
    {
        dprintf(2, "malloc error exec\n");
        exit(EXIT_FAILURE);
    }
   exec->return_value = 0;
   exec->std_in = 0;
   exec->std_out = 1;
   exec->prev = -1;
}

void ft_exec_multi_cmds(save_struct *t_struct, char **envp)
{
    t_cmd *start; 
    t_cmd *end;

    start =  t_struct->cmd;
    while(t_struct->cmd->next)
        t_struct->cmd = t_struct->cmd->next;
    end = t_struct->cmd;
    t_struct->cmd = start;
    t_struct->ast = build_ast_recursive(start, end);
    print_ast(t_struct->ast, 0, ' ');
    t_exec exec;
    set_exec_struct(&exec);
    exec_ast_recursive(t_struct->ast, envp, &exec);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
}
