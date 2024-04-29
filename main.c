#include "minishell.h"

int		g_signal = 0;

void	ft_handler_signals(int signal)
{
	
	if (signal == SIGINT)
		g_signal = 1;
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	t_cmd	*lst;
	t_envp	*envp_lst;

	(void)av;
	(void)ac;
	buffer = NULL;
	lst = NULL;
	envp_lst = NULL;
	envp_lst = ft_save_envp(envp, &envp_lst);
	signal(SIGINT, ft_handler_signals);
	while (1)
	{
		buffer = readline("~$ ");
		if (g_signal == 1)
		{
			
			g_signal = 0;
			free(buffer);
			continue;
		}
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
		lst = NULL;
		ft_free_lst(lst);
	}
	ft_free_envp_lst(envp_lst);
}
