#include "../minishell.h"

void ft_save_envp(char **envp_tab, t_envp **envp_lst)
{
	int		i;

	i = 0;
	while (envp_tab[i])
	{
		add_to_envp_lst(envp_lst, create_envp_node(envp_tab[i]));
		i++;
	}
	return ;
}
