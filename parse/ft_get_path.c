#include "../minishell.h"

int	ft_get_path(t_cmd *node)
{
	char *path;
	char **bin;
	int i;

	path = getenv("PATH");
	if (!path)
		return (-1);           // Error type TODO !
	bin = ft_split(path, ":"); // split les paths
	i = 0;
	while (bin[i])
	{
		if (access(ft_strjoin(bin[i], node->cmd[0]), F_OK) == 0)
		// utiliser strcat pour pas malloc un truc impossible a free ? juste pour la boucle
		{
			node->path = ft_strjoin(bin[i], node->cmd[0]);
			break ;
		}
		i++;
	}

	ft_free_tab(bin);
	return (0);
}