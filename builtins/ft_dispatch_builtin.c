#include "../minishell.h"

int	ft_dispatch_builtin(t_cmd *cmd, save_struct *t_struct)
{
	if (!t_struct->cmd->cmd)
		return (-1);
	ft_expand(cmd, &t_struct->envp);
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (ft_echo(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (ft_export(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (ft_exit(t_struct, &t_struct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (ft_unset(cmd->cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (ft_env(&t_struct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (ft_pwd(cmd->cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (ft_cd(t_struct));
	return (-1);
}
