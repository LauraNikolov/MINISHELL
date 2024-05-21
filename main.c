#include "minishell.h"

// int	ft_check_brackets(t_cmd **cmd)
// {
// 	t_cmd	*curr;
// 	int		i;

// 	if (!*cmd || !cmd)
// 		return (0);
// 	curr = *cmd;
// 	i = -1;
// 	while (curr && curr->type != O_BRACKET)
// 		curr = curr->next;
// 	while (curr && curr->type == O_BRACKET)
// 	{
// 		i++;
// 		curr = curr->next;
// 	}
// 	while (curr && curr->type != C_BRACKET && curr->type != O_BRACKET)
// 		curr = curr->next;
// 	while (curr && curr->next && curr->type == C_BRACKET
// 		&& curr->type != O_BRACKET)
// 	{
// 		i--;
// 		curr = curr->next;
// 	}
// 	if (i != 0 || !(*cmd)->next || curr->type == O_BRACKET)
// 		ft_putstr_cmd_fd("syntax error near unexpected token `", 2,
// 			curr->cmd[0]);
// 	return (0);
// }

static int	ft_tokenize(char **envp, char *buffer, save_struct *t_struct)
{
	int		(*ft_tab[10])(t_cmd *);
	t_cmd	*curr;
	char	*save_spaces;
	int		bool_bracket;

	bool_bracket = 0;
	curr = t_struct->cmd;
	while (curr)
	{
		curr->bool_bracket = &bool_bracket;
		curr = curr->next;
	}
	save_spaces = NULL;
	ft_save_envp(envp, &(t_struct->envp));
	ft_create_token_lst(buffer, &(t_struct->cmd), &save_spaces);
	ft_remove_null_node(&(t_struct->cmd));
	ft_export_cmd(&(t_struct->envp), t_struct->cmd->cmd);
	ft_clean_cmd_lst(&(t_struct->cmd), &save_spaces);
	// ft_check_brackets(&(t_struct->cmd));
	ft_init_ft_tab(ft_tab);
	ft_exec_syntax_functions(&(t_struct->cmd), ft_tab);
	bool_bracket = 0;
	free(save_spaces);
	return (0);
}

void	ft_handler_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		// g_signal = 1;
	}
}
void	ft_all_free(save_struct *t_struct)
{
	ft_free_lst(t_struct->cmd);
	// free(t_struct);
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
			return (free(buffer), ft_all_free(t_struct), free(t_struct), 0);
		ft_tokenize(envp, buffer, t_struct);
		ft_print_lst(t_struct->cmd);
		ft_exec(t_struct, envp);
		ft_all_free(t_struct);
		free(buffer);
		buffer = NULL;
	}
}
