#include "../minishell.h"

int	ft_exit(char **code, t_envp **env)
{
	if (code[2])
		ft_putstr_cmd_fd("Minishell: exit: too many arguments", 2, NULL, 0);
	else if (!ft_str_isdigit(code[1]) || ft_atoll(code[1]) > LONG_MAX
		|| ft_atoll(code[1]) < 0)
	{
		ft_putstr_cmd_fd("Minishell: exit: ", 2, NULL, 2);
		ft_putstr_cmd_fd(code[1], 2, NULL, 2);
		ft_putstr_cmd_fd(": numeric argument required", 2, NULL, 0);
		ft_putstr_cmd_fd("Exit", 1, NULL, 0);
	}
	else
		ft_putstr_cmd_fd("Exit", 1, NULL, 0);
	ft_return_code(ft_itoa(atoi(code[1]) % 256), env);
	exit(atoi(code[1]) % 256);
	return (0);
}
