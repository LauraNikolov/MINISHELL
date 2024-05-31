#include "../minishell.h"

/* char	*ft_find_match(char *s, char *d_name)
{
}

char	**ft_stars(char *s)
{
	int				i;
	int				j;
	int				k;
	DIR				*dir;
	struct dirent	*entry;
	char			*match;
	int				match;

	match = 0;
	if (!s)
		return (NULL);
	printf("s = %s\n", s);
	i = 0;
	if (!dir)
		dir = readdir(".");
	entry = readdir(dir);
	while (entry)
	{
		i = 0;
		while (entry->d_name[j])
		{
			if (s[i] == entry->d_name[j] && s[i] != '*')
			{
				while (s[i] == entry->d_name[j])
				{
					i++;
					j++;
				}
				if (s[i] == '*')
				{
					match = 1;
					i++;
				}
			}
			if (s[i - 1] == '*' && !match)
				break ;
			j++;
		}
		entry = readdir(dir);
	}
	printf("match = %s\n", match);
}

char	**ft_extand_dir(t_cmd **lst, struct dirent *entry, DIR *dir)
{
	char	**wildcard;
	t_cmd	*curr;
	int		i;
	int		j;

	curr = *lst;
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
		{
			while (curr->cmd[i][j])
			{
				if (curr->cmd[i][j] == '*')
					wildcard = ft_stars(curr->cmd[i]);
				j++;
			}
			i++;
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
	wildcard = ft_extand_dir(lst, entry);
	i = 0;
	while (wildcard[i])
	{
		printf("wild[%d] = %s\n", i, wildcard[i]);
		i++;
	}
	closedir(dir);
	return (wildcard);
} */
