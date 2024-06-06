#include "../minishell.h"

int	ft_count_dir(void)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;

	i = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (-1); // Retournez une valeur d'erreur appropriée
	}
	entry = readdir(dir);
	while (entry)
	{
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}

int	ft_is_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_match(char *cmd, char *dir)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i] && cmd[i] != '*')
		i++;
	while (cmd[k + i] && cmd[k + i] == '*')
		k++;
	if (!ft_strncmp(cmd, dir, i))
	{
		if (!cmd[i + k] && !dir[i])
			return (1);
		while (cmd[i + k] && dir[j] && cmd[i + k] != dir[j])
			j++;
		// if (!ft_is_char(dir, dir[j]))
		// {
		// 	printf("j = %d\n", j);
		// 	return (0);
		// }
		return (ft_match(&cmd[i + k], &dir[j]));
	}
	return (0);
}

char	**ft_find_dir(char *cmd, char **dir)
{
	int		i;
	int		j;
	char	**wildcard;

	i = 0;
	j = 0;
	wildcard = malloc(sizeof(char *) * (ft_count_dir() + 1));
	if (!wildcard)
		return (NULL);
	while (dir[i])
	{
		if (ft_match(cmd, dir[i]))
		{
			wildcard[j] = ft_strdup(dir[i]);
			j++;
		}
		i++;
	}
	wildcard[j] = NULL;
	return (wildcard);
}

char	**ft_save_dir(void)
{
	char			**curr_dir;
	struct dirent	*entry;
	DIR				*dir;
	int				i;

	i = 0;
	curr_dir = malloc(sizeof(char *) * (ft_count_dir() + 1));
	if (!curr_dir)
		return (NULL);
	dir = opendir(".");
	if (!dir)
	{
		ft_putstr_cmd_fd("Problem while accessing current directory", 2, NULL);
		free(curr_dir);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		curr_dir[i] = ft_strdup(entry->d_name);
		i++;
		entry = readdir(dir);
	}
	curr_dir[i] = NULL;
	closedir(dir);
	return (curr_dir);
}

int ft_is_wild(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int		count_tab(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**new_tab(char	**tab, char **dir)
{
	int		i;
	int		wild_len;
	int		tab_len;
	char	**wild_tab;
	char	**new_tab;
	int		j;
	int		k;

	i = 0;
	wild_len = 0;
	tab_len = 0;
	new_tab = NULL;
	while (tab[i])
	{
		j = 0;
		if (ft_is_wild(tab[i]))
		{
			if (new_tab)
				free(new_tab);
			wild_tab = ft_find_dir(tab[i], dir);
			wild_len = count_tab(wild_tab);
			printf("wildlen=%d\n", wild_len);
			tab_len = count_tab(tab);
			printf("tablen=%d\n", tab_len);
			new_tab = ft_calloc(tab_len + wild_len + 1, sizeof(char *));
		}
		if (wild_len)
		{
			while (j < tab_len + wild_len - 1)
			{
				k = 0;
				if (j == i)
				{
					while (k < wild_len)
						new_tab[j++] = wild_tab[k++];
				}
				if (j < tab_len + wild_len - 1)
					new_tab[j] = tab[j - k];
				j++;
			}
			free(tab);
			tab = ft_strdup_array(new_tab);
		}
		i++;
	}
	return (tab);
}

void	ft_wildcard(t_cmd **lst)
{
	t_cmd	*curr;
	char	**curr_dir;

	curr_dir = ft_save_dir();
	curr = *lst;
	while (curr)
	{
		if (curr->cmd)
			new_tab(curr->cmd, curr_dir);
		curr = curr->next;
	}
	ft_free_tab(curr_dir);
}




