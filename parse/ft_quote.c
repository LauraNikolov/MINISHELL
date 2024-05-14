#include "../minishell.h"

// int	ft_quote_len(char *s)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		while ((s[i] != '\"' || s[i] != '\'') && s[i] != '\'')
// 		{
// 			len++;
// 			i++;
// 		}
// 		while (s[i] == ' ')
// 		{
// 			if (s[i] && s[i + 1] != ' ')
// 				len--;
// 			len++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	return (i - len);
// }




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
		return (1);
	return (-1);
}
