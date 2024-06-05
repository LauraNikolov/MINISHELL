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
		if (!ft_is_char(dir, dir[j]))
		{
			printf("j = %d\n", j);
			return (0);
		}
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

int	ft_wild(char **cmd, char **dir)
{
	int		i;
	int		j;
	int		len;
	int		dir_index;
	char	**tab;

	len = 0;
	dir_index = 0;
	i = 0;
	while (cmd[i])
		i++;
	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '*')
			{
				while (dir[dir_index])
					if (ft_match(cmd[i], dir[dir_index]))
						len++;
				tab = malloc(sizeof(char *) * (i + len + 1));
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_wildcard(t_cmd **lst)
{
	t_cmd	*curr;
	char	**curr_dir;
	int		i;
	int		j;

	curr_dir = ft_save_dir();
	curr = *lst;
	while (curr)
	{
		i = 1;
		while (curr->cmd[i])
		{
			j = 0;
			while (curr->cmd[i] && curr->cmd[i][j])
			{
				if (curr->cmd[i][j] == '*')
					curr->cmd = ft_wild(curr, curr_dir);
				j++;
				break ;
			}
			i++;
		}
		curr = curr->next;
	}
	ft_free_tab(curr_dir);
}
