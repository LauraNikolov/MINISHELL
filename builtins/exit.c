#include "../minishell.h"

int	ft_exit(save_struct *t_struct, t_envp **envp)
{
	char	**code;

	code = t_struct->cmd->cmd;
	if (!code[1])
	{
		ft_putstr_cmd_fd("Exit", 2, NULL, 0);
		ft_free_envp_lst(envp);
		ft_all_free(t_struct);
		exit(ft_atoi(ft_search_var("?", envp)));
	}
	if (ft_str_isdigit(code[1]) && !code[2])
	{
		ft_putstr_cmd_fd("Exit", 2, NULL, 0);
		ft_free_envp_lst(envp);
		ft_all_free(t_struct);
		exit(ft_atoi(code[1]));
	}
	else if (ft_str_isdigit(code[1]) && code[2])
	{
		ft_putstr_cmd_fd("exit", 2, NULL, 0);
		ft_putstr_cmd_fd("Minishell: exit: too many arguments", 2, NULL, 0);
		ft_return_code(ft_strdup("1"), envp);
	}
	else if (ft_str_is_alpha(code[1]))
	{
		ft_putstr_cmd_fd("exit", 2, NULL, 0);
		ft_putstr_cmd_fd("Minishell: exit: ", 2, NULL, 2);
		ft_putstr_cmd_fd(code[1], 2, NULL, 2);
		ft_putstr_cmd_fd(": numeric argument required", 2, NULL, 0);
		ft_free_envp_lst(envp);
		ft_all_free(t_struct);
		exit(156);
	}
	else if (ft_str_isdigit(code[1]) || ft_atoll(code[1]) > LONG_MAX
		|| ft_atoll(code[1]) < 0)
	{
		ft_putstr_cmd_fd("Minishell: exit: ", 2, NULL, 2);
		ft_putstr_cmd_fd(code[1], 2, NULL, 2);
		ft_putstr_cmd_fd(": numeric argument required", 2, NULL, 0);
		ft_putstr_cmd_fd("Exit", 2, NULL, 0);
		ft_free_envp_lst(envp);
		ft_all_free(t_struct);
		exit(2);
	}
	return (0);
}
