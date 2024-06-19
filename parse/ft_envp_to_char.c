#include "../minishell.h"

/* int	ft_lst_env_size(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static int	ft_var_size(t_envp *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	if (node->var_name)
		while (node->var_name[i])
			i++;
	if (node->var_value)
		while (node->var_value[i])
			i++;
	return (i + 1);
}

char	**ft_envp_to_char(t_envp **env)
{
	char	**envp;
	int		i;
	int		j;

	j = 0;
	envp = malloc(sizeof(char *) * (ft_lst_env_size(*env) + 1));
	while (env)
	{
		i = 0;
		envp[j++] = malloc(ft_safe_malloc(&envp[i], ft_var_size(envp[i])));
		env = env->next;
	}
} */
