#include "../minishell.h"

int ft_dispatch_builtin(char **cmd, save_struct *t_struct)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return(ft_echo(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "export"))
		return(ft_export(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "exit"))
		return(ft_exit(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "unset"))
		return(ft_unset(cmd, &t_struct->envp));
	else if (!ft_strcmp(cmd[0], "env"))
		return(ft_print_envp(&t_struct->envp));
	return (0);
}
