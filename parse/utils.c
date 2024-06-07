#include "../minishell.h"

int	ft_safe_malloc(char **s, int size)
{
	if (!s)
		return (0);
	*s = ft_calloc(size + 100, sizeof(char));
	if (!*s)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_is_symb(char *cmd, char *symb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (symb[i] && cmd[j]) // gerer les double chevrons et les && et les ||
	{
		if (cmd[j] == symb[i])
			return (1);
		i++;
	}
	return (0);
}

char	**ft_strdup_array(char **cmd)
{
	int		i;
	char	**cpy;

	cpy = NULL;
	i = 0;
	if (!cmd || !*cmd)
		return NULL;
	while (cmd[i])
		i++;
	cpy = malloc((i + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		cpy[i] = ft_strdup(cmd[i]);
		if (!cpy[i])
		{
			while (i > 0)
				free(cpy[--i]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	ft_free_tab(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	ft_str_is_alpha(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 'a' || s[i] > 'z') || (s[i] < 'A' || s[i] > 'Z'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_putstr_cmd_fd(char *s, int fd, char *str)
{
	int	i;

	i = 0;
	write(fd, s, ft_strlen(s));
	if (str)
		write(fd, str, ft_strlen(str));
	write(fd, "\'", 2);
	write(fd, "\n", 2);
	return (-1);
}
