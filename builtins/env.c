#include "../minishell.h"

void	ft_env(char **envp) // commande env a executer directement sur le char **envp et pas sur la liste envp
{
	int i;

	i = -1;
	if (!*envp || !envp)
		ft_putstr_fd("minishell , environment is empty or null", 2);
	while(envp[++i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
	}
}
