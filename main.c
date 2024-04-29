#include "minishell.h"

void	ft_save_envp(char **envp_tab)
{
	t_envp	*envp;
	int		i;

	envp = malloc(sizeof(t_envp));
	i = 0;
	while (envp_tab[i])
	{
		envp->var_name = envp_tab[i];
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	t_cmd	*lst;

	(void)av;
	(void)ac;
	buffer = NULL;
	lst = NULL;
	ft_save_envp(envp);
	while (1)
	{
		buffer = readline("~$ ");
		if (!buffer)
			return (0);
		if (buffer[0] == '\0')
			return (0);
		ft_create_token_lst(buffer, &lst);
		ft_get_path(&lst);
		// ft_exec_cmd();
		ft_print_lst(lst);
		free(buffer);
		buffer = NULL;
		ft_free_lst(lst);
		lst = NULL;
	}
}
