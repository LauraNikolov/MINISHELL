#include "../minishell.h"

int	ft_var_strlen(char *s, t_envp **env, int *len, int *i)
{
	char	*var;
	int		index;
	char	*var_value;
	int		var_size;

	index = *i + 1;
	if (s[*i + 1] == '{')
	{
		var_size = ft_var_len(&s[*i + 2], 1);
		*len += 2;
		index++;
		(*i)++;
	}
	else
		var_size = ft_var_len(&s[*i + 1], 0);
	var = ft_strndup(&s[index], var_size);
	printf("VAR = %s\n", var);
	var_value = ft_search_var(var, env);
	free(var);
	return (ft_strlen(var_value) - ft_strlen(var)); // calcul again the value
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
	i = 0;
	quote_len = 0;
	c = '\0';
	while (s[i] && i < len)
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			quote_len++;
		}
		else if (s[i] == '$' && c != '\'' && (ft_isalnum(s[i + 1]) || s[i
			+ 1] == '_' || s[i + 1] == '{'))
		{
			var_size += ft_var_strlen(s, env, &len, &i);
			len++;
		}
		i++;
	}
	if (quote_len % 2 != 0)
		ft_putstr_cmd_fd("Quote are odd !\n", 2, NULL);
	return (100);
}
