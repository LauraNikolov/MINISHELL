#include "../minishell.h"

int	ft_env(t_envp **envp)
{
	int	i;

	i = -1;
	if (!*envp || !envp)
	{
		ft_putstr_fd("minishell , environment is empty or null", 2);
		ft_return_code("127", envp);
	}
	ft_print_envp(envp);
	return (ft_return_code(0, envp));
}
