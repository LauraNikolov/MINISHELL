#include "../minishell.h"

int	ft_var_strlen(char *s, t_envp **env)
{
	int		i;
	int		len;
	char	*var;

	i = 0;
	while (s[i] && (s[i] != ' ' || s[i] != '\"'))
		i++;
	var = ft_strndup(s, i);
	len = ft_strlen(ft_search_var(var, env));
	free(var);
	return (len);
}

int	ft_quote_len(char *s, t_envp **env)
{
	int		i;
	int		len;
	int		var_size;
	int		quote_flag;
	char	c;

	quote_flag = -1;
	var_size = 0;
	i = -1;
	len = 0;
	c = '\0';
	while (s[++i])
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			len++;
		}
		if (c == '\"' && s[i] == '$')
			var_size += ft_var_strlen(&s[i + 1], env);
	}
	if (len % 2 != 0)
		ft_putstr_cmd_fd("WARNING quote are odd !\n", 2, NULL);
	return (i - len + var_size);
}

/* int	ft_quote_len(char *s)
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
} */
