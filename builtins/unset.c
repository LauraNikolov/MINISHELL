#include "../minishell.h"

static void	ft_remove_var(t_envp *node)
{
	if (!node)
		return ;
	if (node->next)
		node->next->prev = node->prev;
	else
		node->prev->next = NULL;
	if (node->prev)
		node->prev->next = node->next;
	else
		node->next->prev = NULL;
	free(node->var_name);
	free(node->var_value);
	free(node);
}

int	ft_unset(save_struct *t_struct, char **var)
{
	t_envp	*curr;
	t_envp	*tmp;
	int		i;

	curr = t_struct->envp;
	while (curr)
	{
		tmp = curr->next;
		i = -1;
		while (var[++i])
			if (!ft_strcmp(curr->var_name, var[i]))
			{
				if (!curr->prev)
					t_struct->envp = tmp;
				ft_remove_var(curr);
			}
		curr = tmp;
	}
	return (ft_return_code("0", &t_struct->envp));
}
