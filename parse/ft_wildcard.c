#include "../minishell.h"

int	ft_extand_dir(t_cmd **lst, DIR *dir, struct dirent *entry)
{
	char	**wildcard;
	t_cmd	*curr;
	int		i;
	int		j;

	j = 0;
	curr = *lst;
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
		{
			if (curr->cmd[i][j] == '*')
				ft_find_dir();
			j++;
		}
		curr = curr->next;
	}
	return (wildcard);
}

char	**ft_wildcard(t_cmd **lst)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**wildcard;
	int				i;

	dir = opendir(".");
	if (dir == NULL)
		return (ft_putstr_cmd_fd("Error while accessing directory\n", 2, NULL),
			NULL);
	entry = readdir(dir);
	wildcard = ft_extand_dir(lst, dir, entry);
	i = 0;
	while (wildcard[i])
	{
		printf("wild[%d] = %s\n", i, wildcard[i]);
		i++;
	}
	closedir(dir);
	return (wildcard);
}
