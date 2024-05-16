#include "minishell.h"
#include "struct.h"

int			g_signal = 0;

void	ft_clean_cmd_lst(t_cmd **lst, char **save_spaces)
{
	t_cmd	*curr;
	int		i;
	int		j;
	int		k;

	curr = *lst;
	ft_remove_null_node(lst);
	i = 0;
	j = 0;
	k = 0;
	printf("save_spaces %s\n", *save_spaces);
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
		{
			j = 0;
			while (curr->cmd[i][j])
			{
				if (curr->cmd[i][j] == '%' && *save_spaces[k] == '1')
				{
					printf ("Save_spaces[k] = %c\n", *save_spaces[k]);
					curr->cmd[i][j] = ' ';
				}
				j++;
				k++;
			}
			i++;
		}
		curr = curr->next;
	}
	free(*save_spaces);
}

static int	ft_tokenize(char **envp, char *buffer, save_struct *t_struct)
{
	int		(*ft_tab[10])(t_cmd *);
	t_cmd	*curr;
	char	*save_spaces;

	save_spaces = NULL;
	(void)envp;
	// ft_save_envp(envp, &(t_struct->envp));
	ft_create_token_lst(buffer, &(t_struct->cmd), &save_spaces);
	ft_clean_cmd_lst(&(t_struct->cmd), &save_spaces);
	ft_init_ft_tab(ft_tab);
	curr = t_struct->cmd;
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
void	ft_all_free(save_struct *t_struct)
{
	ft_free_lst(t_struct->cmd);
	free(t_struct);
}

int	main(int ac, char **av, char **envp)
{
	char		*buffer;
	save_struct	*t_struct;

	(void)av;
	(void)ac;
	buffer = NULL;
	signal(SIGINT, ft_handler_signals);
	while (1)
	{
		t_struct = malloc(sizeof(save_struct));
		ft_memset(t_struct, 0, sizeof(*t_struct));
		buffer = readline(CYAN "MINISHELL~ " RESET);
		if (!buffer)
			return (free(buffer), ft_all_free(t_struct), 0);
		ft_tokenize(envp, buffer, t_struct);
		ft_print_lst(t_struct->cmd);
		ft_print_envp(t_struct->envp);
		ft_exec(t_struct, envp);
		ft_all_free(t_struct);
		free(buffer);
		buffer = NULL;
	}
}
