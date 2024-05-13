/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/13 14:27:12 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exec_single_cmd(save_struct *t_struct, char **envp)
{
    int return_value;
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        return_value = execve(t_struct->cmd->path, t_struct->cmd->cmd, envp);
    }
    else if(pid != -1)
    {
        wait(NULL);
    }
    else
    {
        perror("execve\n");
    }
    return(0);    
}