#include "minishell.h"
#include "struct.h"

int			g_signal = 0;

static int	ft_tokenize(char *buffer, t_cmd **lst)
{
	int	(*ft_tab[10])(t_cmd *);

	t_cmd	*curr;
	ft_create_token_lst(buffer, lst);
	ft_init_ft_tab(ft_tab);
	curr = *lst;
	while (curr)
	{
		ft_tab[curr->type](curr);
		curr = curr->next;
	}
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
void ft_all_free(save_struct *t_struct)
{
	ft_free_lst(t_struct->cmd);
	free(t_struct);
}

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	
	(void)av;
	(void)ac;
	buffer = NULL;
	save_struct *t_struct;
	signal(SIGINT, ft_handler_signals);
	while (1)
	{
		t_struct = malloc(sizeof(save_struct));
		ft_memset(t_struct, 0, sizeof(*t_struct));
		buffer = readline(CYAN "MINISHELL~ " RESET);
		if (!buffer)
			return(free(buffer), ft_all_free(t_struct), 0);
		ft_tokenize(buffer, &(t_struct->cmd));
		ft_print_lst(t_struct->cmd);
		ft_exec(t_struct, envp);
		ft_all_free(t_struct);
		free(buffer);
		buffer = NULL;
	}
}
