#include "../minishell.h"

char	*ft_quote(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] && ((s[0] == '\'' && s[ft_strlen(s)] == '\'') || (s[0] == '\"'
				&& s[ft_strlen(s)] == '\"')))
	{
		while (s[i] && (s[i] != '\'' || s[i] != '\"') && s[i + 1] != '\0')
		{
			/* if (s[i] == '$' && s[0] == '\"' && s[i + 1])
				// ft_expand(); TODO */
			ft_putchar_fd(s[i], 1);
			i++;
		}
	}
	return (NULL);
}