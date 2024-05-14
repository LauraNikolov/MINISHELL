#include "../minishell.h"

int	ft_simple_quote(char *s, char **cmd, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		*cmd[i] = s[i];
		i++;
	}
	return (i + 1);
}

int	ft_double_quote(char *s, char **cmd, char c)
{
	(void)s;
	(void)c;
	(void)cmd;
	return (0);
}

int	ft_handle_quote(char *s, char **cmd)
{
	int		i;
	int		j;
	int		quote_status;
	int		(*ft_quote_functions[2])(char *, char **, char c);

	ft_quote_functions[0] = ft_simple_quote;
	ft_quote_functions[1] = ft_double_quote;
	quote_status = 0;
	i = 0;
	j = 0;
	*cmd = malloc(sizeof(char) * 200);
	while (s[i])
	{
		if (s[i] == '\'')
			i+= ft_quote_functions[0](&s[i], cmd, s[i]);
		if (s[i] == '\"')
			i+= ft_quote_functions[1](&s[i], cmd, s[i]);
		while (s[i] && s[i] == ' ')
			i++;
			//cat
		*cmd[j] = ' ';
		*cmd[j] = s[i];
		i++;
		j++;
	}
	*cmd[j] = '\0';
	printf ("cmd = %s\n", *cmd);
	exit(0);
	return (i);
}

static int	ft_get_symb(t_cmd **lst, char *buff, char **cmd, int j)
{
	j = ft_check_double_symbols(&buff[j], cmd);
	add_to_lst(lst, create_cmd_node(*cmd));
	free(*cmd);
	return (j);
}

int	ft_create_token_lst(char *buffer, t_cmd **lst)
{
	char	*cmd;
	int		j;
	int		len;

	j = 0;
	cmd = NULL;
	while (buffer[j])
	{
		len = 0;
		while (buffer[j] && !ft_is_symb(&buffer[j], "|><()&"))
		{
			j++;
			len++;
		}
		ft_handle_quote(&buffer[j - len], &cmd);
		add_to_lst(lst, create_cmd_node(cmd));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(lst, buffer, &cmd, j);
	}
	ft_remove_null_node(lst);
	return (0);
}
