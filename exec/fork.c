/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/13 14:16:38 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_single_cmd(save_struct *t_struct, char **envp)
{
    int return_value;
    pid_t pid;
    int pfd[2];
    pipe(pfd);
    pid = fork;
    if(pid == 0)
    {
        close(pfd[1]);
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        return_value = execve(t_struct->cmd->path, t_struct->cmd->cmd, envp);
    }
    else
    {
        close(pfd[0]);
        wait(NULL);
        close(pfd[1]);
    }
}