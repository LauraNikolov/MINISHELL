/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/13 13:19:31 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_single_cmd(save_struct *t_struct, char **envp)
{
    int return_value;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		// ! check builting
		return_value = ft_dispatch_builtin(t_struct->cmd->cmd, t_struct);
		if(return_value != -1)
			exit(return_value);
		else
        	return_value = execve(t_struct->cmd->path, t_struct->cmd->cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}

void	ft_exec(save_struct *t_struct, char **envp)
{
	int cmd_size;

	cmd_size = ft_lst_size(t_struct->cmd);
	if (cmd_size == 1)
	{
		ft_exec_single_cmd(t_struct, envp);
		return ;
	}
	else
		ft_exec_multi_cmds(t_struct, envp);
}