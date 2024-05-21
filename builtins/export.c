#include "../minishell.h"

void	ft_swap_nodes(t_envp **n1, t_envp **n2)
{
	t_envp	*n1_prev;
	t_envp	*n2_next;
	t_envp	*n1_next;
	t_envp	*n2_prev;

	if (n1 == NULL || *n1 == NULL || n2 == NULL || *n2 == NULL || n1 == n2)
		return ;
	n1_prev = (*n1)->prev;
	n2_next = (*n2)->next;
	// Adjust the pointers of the previous and next nodes
	if (n1_prev)
		n1_prev->next = *n2;
	if (n2_next)
		n2_next->prev = *n1;
	// Swap the prev and next pointers of n1 and n2
	n1_next = (*n1)->next;
	n2_prev = (*n2)->prev;
	if (n1_next == *n2) // Special case: n1 is immediately before n2
	{
		(*n2)->prev = n1_prev;
		(*n2)->next = *n1;
		(*n1)->prev = *n2;
		(*n1)->next = n2_next;
	}
	else if (n2_next == *n1) // Special case: n2 is immediately before n1
	{
		(*n1)->prev = n2_prev;
		(*n1)->next = *n2;
		(*n2)->prev = *n1;
		(*n2)->next = n1_next;
	}
	else // General case: n1 and n2 are not adjacent
	{
		(*n1)->prev = n2_prev;
		(*n1)->next = n2_next;
		(*n2)->prev = n1_prev;
		(*n2)->next = n1_next;
		if (n1_next)
			n1_next->prev = *n2;
		if (n2_prev)
			n2_prev->next = *n1;
	}
}

void	ft_print_env(t_envp **env)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->var_name, 1);
		if (curr->var_value[0])
		{
			write(1, "=\"", 3);
			ft_putstr_fd(curr->var_value, 1);
			write(1, "\"", 2);
		}
		write(1, "\n", 2);
		curr = curr->next;
	}
}

static void	ft_add_var(t_envp **env, char **var)
{
	int		i;
	t_envp	*curr;

	if (!*var || !var || !var[1])
		return ;
	if (var[1][0] >= '0' && var[1][0] <= '9')
		ft_putstr_cmd_fd("bash: export: `': not a valid identifier", 2,
			var[1]);
	i = 0;
	while (var[++i])
		add_to_envp_lst(env, create_envp_node(var[i], 1));
	curr = *env;
	while (curr && !curr->add_variables)
		curr = curr->next;
	while (curr && curr->next)
	{
		if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
		{
			ft_swap_nodes(&curr, &curr->next);
			curr = *env;
		}
		else
			curr = curr->next;
	}
}

int	ft_export_cmd(t_envp **env, char **var)
{
	t_envp	*curr;

	if (!*env || !env)
		return (0);
	curr = *env;
	while (curr->next && !curr->add_variables)
	{
		if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
		{
			ft_swap_nodes(&curr, &curr->next);
			curr = *env;
		}
		else
			curr = curr->next;
	}
	ft_add_var(env, var);
	ft_print_env(env);
	return (0);
}
