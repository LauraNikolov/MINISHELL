#include "../minishell.h"

int	ft_get_path(t_cmd **lst)
{
	t_cmd *curr;
	char *path;
	char **bin;
	int i;

	path = getenv("PATH");
	curr = *lst;
	if (!path)
		return (-1);           // Error type TODO !
	bin = ft_split(path, ":"); // split les paths
	while (curr)
	{
		i = 0;
		while (bin[i])
		{
			if (access(ft_strjoin(bin[i], curr->cmd[0]), F_OK) == 0)
				// utiliser strcat pour pas malloc un truc impossible a free ? juste pour la boucle
			{
				curr->path = ft_strjoin(bin[i], curr->cmd[0]);
				break ;
			}
			i++;
		}
		curr = curr->next;
	}
	ft_free_tab(bin);
	return (0);
}