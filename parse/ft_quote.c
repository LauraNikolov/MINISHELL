#include "../minishell.h"

int	ft_var_strlen(char *s, t_envp **env)
{
	int		i;
	int		len;
	char	*var;
	char	*var_value;

	i = 0;
	len = 0;
	while ((s[i] && s[i] != ' ') && (s[i] && s[i] != '\"'))
		i++;
	var = ft_strndup(&s[1], i - 1);
	var_value = ft_search_var(var, env);
	if (var_value)
		len = ft_strlen(var_value) - ft_strlen(var);
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
		if ((c == '\"' && s[i] == '$') || (s[i] == '$' && c != '\''))
			var_size += ft_var_strlen(&s[i], env);
		i++;
	}
	if (len % 2 != 0)
		ft_putstr_cmd_fd("WARNING quote are odd !\n", 2, NULL);
	return (i - len + var_size);
}

// int	ft_quote_len(char *s)
// {
// 	int		i;
// 	int		len;
// 	int		quote_flag;
// 	char	c;

// 	quote_flag = -1;
// 	i = 0;
// 	len = 0;
// 	c = '\0';
// 	while (s[i])
// 	{
// 		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
// 				&& s[i] == '\'') || (s[i] == c))
// 		{
// 			quote_flag *= -1;
// 			c = s[i];
// 			len++;
// 		}
// 		i++;
// 	}
// 	if (len % 2 != 0)
// 	{
// 		exit (printf("WARNING quote are odd !\n"));
// 	}
// 	return (i - len);
// }
