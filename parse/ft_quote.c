#include "../minishell.h"

int	ft_cmd_len(char *s, t_envp **env, int *i)
{
	char	*var;
	char	*var_value;
	int		var_len;

	var = NULL;
	var_len = 0;
	(*i)++;
	if (s[*i] == '{')
	{
		(*i)++;
		var_len = ft_var_len(&s[*i], 1);
		var = ft_strndup(&s[*i], var_len);
		*i += var_len + 1;
		var_len += 3;
	}
	else
	{
		var_len = ft_var_len(&s[*i], 0);
		var = ft_strndup(&s[*i], var_len);
		*i += var_len;
		var_len++;
	}
	(*i)--;
	var_value = ft_search_var(var, env);
	free(var);
	return (ft_strlen(var_value) - var_len);
}

int	ft_quote_len(char *s, t_envp **env, int len)
{
	int		i;
	int		var_size;
	int		quote_flag;
	int		quote_len;
	char	c;

	quote_flag = -1;
	var_size = 0;
	i = -1;
	quote_len = 0;
	c = '\0';
	while (s[++i] && i < len)
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			quote_len++;
		}
		else if (s[i] == '$' && c != '\'' && s[i + 1])
			var_size += ft_cmd_len(s, env, &i);
	}
	if (quote_len % 2 != 0)
		ft_putstr_cmd_fd("Quote are odd !\n", 2, NULL);
	return (i + var_size - quote_len);
}
