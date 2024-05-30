#include "../minishell.h"

int	ft_var_strlen(char *s, t_envp **env, int *len, int *index)
{
	int		i;
	int		start;
	char	*var;
	char	*var_value;

	i = 1;
	start = 1;
	if (s[i] == '{')
	{
		ft_check_braces(&s[i]);
		*len += 2;
		*index += 1;
		start = 2;
		i++;
	}
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	var = ft_strndup(&s[start], i - 1);
	*index += i - 1;
	var_value = ft_search_var(var, env);
	len += ft_strlen(var);
	free(var);
	return (ft_strlen(var_value) + 10); // calcul again the value 
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
		else if (s[i] == '$' && c != '\'' && (ft_isalnum(s[i + 1]) || s[i
			+ 1] == '_' || s[i + 1] == '{'))
			var_size += ft_var_strlen(&s[i], env, &len, &i);
		i++;
	}
	if (len % 2 != 0)
		ft_putstr_cmd_fd("Quote are odd !\n", 2, NULL);
	return (i + var_size - len);
}
