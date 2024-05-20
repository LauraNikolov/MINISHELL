#include "../minishell.h"

void	ft_swap_nodes(t_envp **n1, t_envp **n2)
{
	t_envp	*tmp;
	t_envp	*n1_prev;
	t_envp	*n2_next;

	n1_prev = (*n1)->prev;
	n2_next = (*n2)->next;

	if (n1_prev)
		n1_prev->next = *n2;
	if (n2_next)
		n2_next->prev = *n1;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;

	(*n1)->prev = n1_prev;
	(*n2)->next = n2_next;
}

int	ft_not_sorted(t_envp *node)
{
	while (node->next)
	{
		if (ft_strcmp(node->var_name, node->next->var_name) > 0)
			return (1);
		node = node->next;
	}
	return (0);
}

static void	ft_print_env(t_envp **env)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->var_name, 1);
		write(1, "=\"", 3);
		ft_putstr_fd(curr->var_value, 1);
		write(1, "\"\n", 3);
		curr = curr->next;
	}
}

int	ft_export_cmd(t_envp **env)
{
	t_envp	*curr;

	if (!*env || !env)
		return (0);
	curr = *env;
	while (curr->next && ft_not_sorted(curr))
	{
		if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
		{
			ft_swap_nodes(&curr, &curr->next);
			curr = *env;
		}
		else
			curr = curr->next;
	}
	ft_print_env(env);
	return (0);
}
