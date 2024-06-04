/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/31 14:44:00 by lauranicolo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_exec_single_cmd(save_struct *t_struct, char **envp)
{
    pid_t pid;
    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        execve(t_struct->cmd->path, t_struct->cmd->cmd, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
    return 0;
}



void ft_exec(save_struct *t_struct, char **envp)
{
    int cmd_size;
    
    cmd_size = ft_lst_size(t_struct->cmd);
    ft_get_path(t_struct->cmd);
    if(cmd_size == 1)
    {
        ft_exec_single_cmd(t_struct, envp);
        return ;
    }
    else
       ft_exec_multi_cmds(t_struct, envp);
}