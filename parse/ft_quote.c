#include "../minishell.h"

int	ft_var_strlen(char *s, t_envp **env)
{
	int		i;
	char	*var;
	char	*var_value;

	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	var = ft_strndup(&s[i], i - 1);
	var_value = ft_search_var(var, env);
	free(var);
	return (ft_strlen(var_value));
}

int	ft_quote_len(char *s, t_envp **env)
{
	int		i;
	int		quote_len;
	int		var_size;
	int		quote_flag;
	char	c;

	quote_flag = -1;
	var_size = 0;
	i = 0;
	quote_len = 0;
	c = '\0';
	while (s[i])
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			quote_len++;
		}
		else if (s[i] == '$' && c != '\'')
		{
			var_size += ft_var_strlen(&s[i], env);
			i += var_size;
		}
		i++;
	}
	if (quote_len % 2 != 0)
		ft_putstr_cmd_fd("WARNING quote are odd !\n", 2, NULL);
	return (quote_len + var_size);
}
