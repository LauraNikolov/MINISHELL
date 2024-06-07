#include "../minishell.h"

int	ft_tokenize(char *buffer, save_struct *t_struct, t_envp **env)
{
	t_cmd	*curr;
	int		bool_bracket;

	bool_bracket = 0;
	t_struct->envp = *env;
	ft_create_token_lst(buffer, t_struct);
	curr = t_struct->cmd;
	while (curr)
	{
		curr->bool_bracket = &bool_bracket;
		curr = curr->next;
	}
	ft_remove_null_node(&(t_struct->cmd));
	ft_clean_cmd_lst(&(t_struct->cmd), t_struct);
	if (ft_exec_syntax_functions(&(t_struct->cmd)) == -1)
		return (-1);
	ft_wildcard(&(t_struct->cmd));
	bool_bracket = 0;
	// free(t_struct->save_spaces);
	return (0);
}
