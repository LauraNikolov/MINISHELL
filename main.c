#include "minishell.h"

int g_signal;

void	ft_handler_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("minishell : ", 1);
	}
}

void ft_handler_child_signals(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		exit(131);
	}
	if (signal == SIGINT)
		ft_putstr_fd("\n", 1);
}

int ft_signal(int pid)
{
	if (pid != 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler_signals);
	}
	else 
	{
		signal(SIGQUIT, ft_handler_child_signals);
		signal(SIGINT, ft_handler_child_signals);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char		*buffer;
	t_envp		*env;
	save_struct	*t_struct;

	(void)av;
	(void)ac;
	env = NULL;
	ft_save_envp(envp, &env);
	while (1)
	{
		ft_signal(1);
		t_struct = malloc(sizeof(save_struct));
		if (!t_struct)
			return (ft_free_envp_lst(&env), 0);
		ft_memset(t_struct, 0, sizeof(*t_struct));
		buffer = readline("minishell : ");
		if (!buffer)
			return (ft_free_envp_lst(&t_struct->envp), free(buffer), ft_all_free(t_struct),
				0);
		add_history(buffer);
		if (ft_tokenize(buffer, t_struct, &env) != -1)
			ft_exec(t_struct, ft_envp_to_char(t_struct->envp));
		free(buffer);
		ft_all_free(t_struct);
	}
	return (0);
}
