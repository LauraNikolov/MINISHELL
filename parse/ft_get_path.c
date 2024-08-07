#include "../minishell.h"

int ft_access(t_cmd *node, char **abs_path)
{
	if (access(*abs_path, F_OK) == 0)
	{
		node->path = *abs_path;
		return (1);
	}
	ft_safe_free(abs_path);
	return (0);
}

void	ft_get_path(t_cmd *node)
{
	char	*path;
	char	*absolute_path;
	char	**bin;
	int		i;

	if (!node->cmd)
		return ;
	path = getenv("PATH");
	bin = ft_split(path, ":");
	i = -1;
	while (bin[++i])
	{
		absolute_path = ft_strjoin_path(bin[i], node->cmd[0]);
		if (ft_access(node, &absolute_path) == 1)
			break ;
	}
	if (!ft_access(node, &absolute_path))
	{
		ft_safe_free(&node->path);
		node->path = ft_strdup(node->cmd[0]);
	}
	ft_free_tab(bin);
}
