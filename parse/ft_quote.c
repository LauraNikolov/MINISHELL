#include "../minishell.h"

char	*ft_quote(char *s)
{
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\'')
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
}