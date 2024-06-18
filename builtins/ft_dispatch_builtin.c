#include "../minishell.h"

int	ft_dispatch_builtin(char **cmd, save_struct *t_struct)
{
	if (!t_struct->cmd->cmd)
		return (-1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(&t_struct->envp));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(&t_struct->envp));
	else if (!ft_strcmp(cmd[0], "cd"))
	{
	dprintf(2, "cmd == %s\n", cmd[0]);
		return (ft_cd(cmd, t_struct));
	}
	return (-1);
}
