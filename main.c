#include "minishell.h"

int			g_signal = 0;

static int	ft_tokenize(char *buffer, t_cmd **lst)
{
	// t_cmd	*curr;

	ft_create_token_lst(buffer, lst);
	// curr = *lst;
	// while (curr)
	// {
	// 	if (ft_check_syntax(curr) == -1)
	// 		return (-1);
	// 	curr = curr->next;
	// }
	 return (0);
}

void	ft_handler_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		g_signal = 1;
	}
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
		buffer = readline(CYAN "MINISHELL~ " RESET);
		if (!buffer)
			return (0);
		if (buffer[0] == '\0')
			return (0);
		ft_tokenize(buffer, &lst);
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
