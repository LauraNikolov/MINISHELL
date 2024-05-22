#include "../minishell.h"

int	ft_tokenize(char *buffer, save_struct *t_struct)
{
	int (*ft_tab[10])(t_cmd *);
	t_cmd *curr;
	char *save_spaces;
	int bool_bracket;

	bool_bracket = 0;
	save_spaces = NULL;
	ft_create_token_lst(buffer, &(t_struct->cmd), &save_spaces);
	curr = t_struct->cmd;
	while (curr)
	{
		curr->bool_bracket = &bool_bracket;
		curr = curr->next;
	}
	ft_remove_null_node(&(t_struct->cmd));
	ft_clean_cmd_lst(&(t_struct->cmd), &save_spaces);
	ft_init_ft_tab(ft_tab);
	ft_exec_syntax_functions(&(t_struct->cmd), ft_tab);
	bool_bracket = 0;
	free(save_spaces);
	return (0);
}