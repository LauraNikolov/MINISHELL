#include "libft.h"

int	ft_count_str(char **t1, char **t2)
{
	int	i;
	int	j;

	i = 0;
	while (t1[i])
		i++;
	while (t2[j])
		j++;
	return (i + j);
}

char	**ft_jointab(char **tab1, char **tab2)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!tab1 || !tab2)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_count_str(tab1, tab2) + 1));
	if (!str)
		return (NULL);
	while (tab1[j])
	{
		str[i] = ft_strdup(tab1[j]);
		if (!str[i])
		{
			while (--i >= 0)
				free(str[i]);
			free(str);
			return (NULL);
		}
		i++;
		j++;
	}
	j = 0;
	while (tab2[j])
	{
		str[i] = ft_strdup(tab2[j]);
		if (!str[i])
		{
			while (--i >= 0)
				free(str[i]);
			free(str);
			return (NULL);
		}
		i++;
		j++;
	}
	str[i] = NULL;
	return (str);
}
