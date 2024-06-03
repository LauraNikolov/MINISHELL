#include "../minishell.h"

char	*ft_find_dir(char *cmd, DIR *dir)
{
	struct dirent	*entry;
	int				i;
	int				j;

	j = 0;
	i = 0;
	entry = readdir(dir);
	if (!entry)
	{
		dir = opendir(".");
		entry = readdir(dir);
	}
	while (cmd[i] && cmd[i] != '*')
		i++;
	if (!ft_strncmp(cmd, entry->d_name, i))
	{
		while (cmd[i] != entry->d_name[j])
			j++;
		ft_find_dir(&cmd[i + 1], &entry->d_name[j]);
	}
	if (!cmd)
		return (ft_strdup(entry->d_name));
	return (NULL);
}

int	ft_count_dir(DIR *dir)
{
	int				i;
	struct dirent	*entry;

	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		i++;
		entry = readdir(dir);
	}
	return (i);
}

char	**ft_wildcard(t_cmd **lst)
{
	DIR		*dir;
	t_cmd	*curr;
	int		i;
	int		j;
	int		k;
	char	**wildcard;

	curr = *lst;
	dir = opendir(".");
	if (dir == NULL)
		return (ft_putstr_cmd_fd("Error while accessing directory\n", 2, NULL),
			NULL);
	wildcard = malloc(sizeof(char *) * ft_count_dir(dir) + 1);
	wildcard[ft_count_dir(dir) + 1] = NULL;
	i = 0;
	k = -1;
	while (curr)
	{
		while (curr->cmd[i])
		{
			j = 0;
			while (curr->cmd[i][j])
			{
				if (curr->cmd[i][j] == '*')
				{
					wildcard[++k] = ft_find_dir(curr->cmd[i], dir);
					break ;
				}
				j++;
			}
			i++;
		}
		curr = curr->next;
	}
	i = 0;
	while (wildcard[i])
	{
		printf("wild[%d] = %s\n", i, wildcard[i]);
		i++;
	}
	closedir(dir);
	exit(0);
	return (wildcard);
}
