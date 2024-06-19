/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/19 19:53:19 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>

void ft_parse_error(t_cmd *cmd)
{
	dprintf(2, "kkkk\n");
	if(ft_strchr(cmd->cmd[0], '/') == -1)
	{
		dprintf(2, "%s: command not found\n", cmd->cmd[0]);
		exit(127);
	}
	else
	{
		dprintf(2 ,"minishell: %s: No such file or directory\n", cmd->cmd[0]);
		exit(126);
	}
}

int	ft_exec_single_cmd(save_struct *t_struct, char **envp)
{
	int return_value;
	pid_t pid;

	if ((return_value = ft_dispatch_builtin(t_struct->cmd->cmd, t_struct)) !=
		-1)
	{
		dprintf(2, "single builtin\n");
		return (return_value);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if(execve(t_struct->cmd->path, t_struct->cmd->cmd, envp) == -1)
			ft_parse_error(t_struct->cmd);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return_value = WEXITSTATUS(status);
	}
	return(return_value);
}

	void ft_exec(save_struct * t_struct, char **envp)
	{
		int cmd_size;

		cmd_size = ft_lst_size(t_struct->cmd);
		if (cmd_size == 1)
		{
			int return_value = ft_exec_single_cmd(t_struct, envp);
			ft_return_code(ft_itoa(return_value), &t_struct->envp);
			return ;
		}
		else
			ft_exec_multi_cmds(t_struct, envp);
	}