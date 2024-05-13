#include "../minishell.h"

int	ft_quote_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while ((s[i] != '\"' || s[i] != '\'') && s[i] != '\'')
		{
			len++;
			i++;
		}
		while (s[i] == ' ')
		{
			if (s[i] && s[i + 1] != ' ')
				len--;
			len++;
			i++;
		}
		i++;
	}
	return (i - len);
}

int	ft_check_quote(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			if (ft_heaven_quote(&s[i], s[i]) == -1)
				printf("quote error\n");
			else
				j = ft_heaven_quote(&s[i], s[i]);
		}
		i += j;
	}
	return (0);
}

int	ft_heaven_quote(char *buff, char c)
{
	int		i;
	char	j;
	int		count;

	count = 0;
	i = 0;
	while (buff[i] != c)
		i++;
	j = ft_strrchr(&buff[i], buff[i]);
	c = buff[i];
	i++;
	while (i < j)
	{
		if (buff[i] == c && buff[i - 1] != '\\')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (j);
	return (-1);
}

// char	*ft_strdup_spaces(char *s, char c)
// {
// 	int i;
// 	int j;
// 	char *res;

// 	res = malloc(sizeof(char) * (ft_quote_len(s, c) + 1));
// 	j = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i] && s[i] == ' ')
// 		{
// 			res[j] = s[i];
// 			j++;
// 		}
// 		while (s[i] && s[i] == ' ')
// 			i++;
// 		while (s[i] != c && s[i] != ' ')
// 			res[j++] = s[i++];
// 	}
// 	printf("%d\n", j);
// 	res[j] = '\0';
// 	printf("res = %s\n", res);
// 	exit(0);
// 	i = 0;
// 	while (s[i] == ' ' || s[i] == '\t')
// 		i++;
// }