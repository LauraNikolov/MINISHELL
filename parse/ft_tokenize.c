#include "../minishell.h"

int	ft_tokenize(char *buffer, t_cmd **lst)
{
	int (*ft_tab[10])(t_cmd *);
	t_cmd *curr;
	char *save_spaces;
	int bool_bracket;

	bool_bracket = 0;
	save_spaces = NULL;
	ft_create_token_lst(buffer, lst, &save_spaces);
	curr = *lst;
	while (curr)
	{
		curr->bool_bracket = &bool_bracket;
		curr = curr->next;
	}
	ft_remove_null_node(lst);
	ft_clean_cmd_lst(lst, &save_spaces);
	ft_init_ft_tab(ft_tab);
	ft_exec_syntax_functions(lst, ft_tab);
	bool_bracket = 0;
	free(save_spaces);
	return (0);
}
