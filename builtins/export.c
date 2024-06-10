#include "../minishell.h"

void	ft_print_env(t_envp **env)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			curr = curr->next;
			continue ;
		}
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
static void	ft_sort_env(t_envp **env, char **var)
{
	t_envp	*curr;

	if (!env || !*env || !*var)
		return ;
	curr = *env;
	while (curr->next)
	{
		if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
		{
			ft_swap_content(&curr->var_name, &curr->next->var_name);
			ft_swap_content(&curr->var_value, &curr->next->var_value);
			curr = *env;
		}
		else
			curr = curr->next;
	}
}

static void	ft_add_var(t_envp **env, char *var)
{
	t_envp	*curr;
	int		flag;

	curr = *env;
	flag = 0;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, var, ft_strchr(var, '=')))
		{
			ft_override_content(curr->var_value, &var[ft_strchr(var, '=') + 1]);
			flag = 1;
		}
		curr = curr->next;
	}
	if (!flag)
		add_to_envp_lst(env, create_envp_node(var));
}
int	ft_export(save_struct *t_struct, char **var)
{
	int	i;

	if (!t_struct->envp || !*var)
		return (0);
	i = -1;
	while (var[++i])
	{
		if ((var[i][0] >= '0' && var[i][0] <= '9') || !ft_isalpha(var[i][0]))
		{
			ft_putstr_cmd_fd("Minishell : export: `", 2, NULL, 2);
			ft_putstr_cmd_fd(var[i], 2, NULL, 2);
			ft_putstr_cmd_fd("': not a valid identifier", 2, NULL, 0);
		}
		else
			ft_add_var(&t_struct->envp, var[i]);
	}
	ft_sort_env(&t_struct->envp, var);
	ft_print_env(&t_struct->envp);
	return (ft_return_code("0", &t_struct->envp));
}
