#include "../minishell.h"

void ft_save_envp(char **envp_tab, t_envp **envp_lst)
{
	int		i;
	char return_code[5];

	i = 0;
	while (envp_tab[i])
	{
		printf ("%s\n",envp_tab[i]);
		add_to_envp_lst(envp_lst, create_envp_node(envp_tab[i]));
		i++;
	}
	return_code[0] = '?';
	return_code[1] = '=';
	return_code[2] = '0';
	add_to_envp_lst(envp_lst, create_envp_node(return_code));
	return ;
}
