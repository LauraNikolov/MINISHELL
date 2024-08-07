#include "../minishell.h"

void	ft_remove_null_node(t_cmd **lst)
{
	t_cmd	*curr;
	t_cmd	*next;

	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (!curr->cmd && !curr->redir)
		{
			if (curr == *lst)
			{
				*lst = next;
				if (next)
					next->prev = NULL;
			}
			else
			{
				curr->prev->next = next;
				if (next)
					next->prev = curr->prev;
			}
			free(curr);
		}
		curr = next;
	}
}

void	ft_clean_cmd_lst(t_cmd **lst, save_struct *t_struct)
{
	t_cmd	*curr;
	int		i;
	int		j;
	int		k;

	curr = *lst;
	k = 0;
	while (curr)
	{
		i = -1;
		if (!curr->cmd)
		{
			curr = curr->next;
			continue ;
		}
		while (curr->cmd[++i])
		{
			j = 0;
			while (curr->cmd[i][j])
			{
				while (t_struct->save_spaces[k])
				{
					if (t_struct->save_spaces[k] != '2')
						break ;
					k++;
				}
				if ((curr->cmd[i][j] == '%' && t_struct->save_spaces[k] == '1'))
					curr->cmd[i][j] = ' ';
				j++;
				k++;
			}
		}
		curr = curr->next;
	}
}
