#include "../minishell.h"

int	ft_quote_len(char *s)
{
	int		i;
	int		len;
	int		quote_flag;
	char	c;

	quote_flag = -1;
	i = 0;
	len = 0;
	c = '\0';
	while (s[i])
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			len++;
		}
		i++;
	}
	if (len % 2 != 0)
	{
		exit (printf("WARNING quote are odd !\n"));
	}
	return (i - len);
}
