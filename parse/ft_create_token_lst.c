#include "../minishell.h"

int	ft_check_double_symbols(char *s, char **cmd)
{
	if (s[0] == '<' && s[1] == '<')
	{
		*cmd = ft_strdup("<<");
		return (2);
	}
	else if (s[0] == '<' && s[1] != '<')
	{
		*cmd = ft_strdup("<");
		return (1);
	}
	else if (s[0] == '>' && s[1] == '>')
	{
		*cmd = ft_strdup(">>");
		return (2);
	}
	else if (s[0] == '&' && s[1] == '&')
	{
		*cmd = ft_strdup("&&");
		return (2);
	}
	else if (s[0] == '|' && s[1] == '|')
	{
		*cmd = ft_strdup("||");
		return (2);
	}
	else if (s[0] == '|' && s[1] != '|')
	{
		*cmd = ft_strdup("|");
		return (1);
	}
	else
	{
		*cmd = ft_strdup(">");
		return (1);
	}
	return (0);
}

int	ft_create_token_lst(char *buffer, t_cmd **lst)
{
	char	*cmd;
	int		j;
	int		len;

	cmd = NULL;
	j = 0;
	len = 0;
	while (buffer[j])
	{
		if (ft_is_symb(&buffer[j], "|><()&") || buffer[j + 1] == '\0')
		{
			if (buffer[j + 1] == '\0')
				cmd = ft_strndup(&buffer[j - len], len + 1);
			else
				cmd = ft_strndup(&buffer[j - len], len);
			if (!cmd)
				return (-1);
			if (cmd)
			{
				add_to_lst(lst, create_cmd_node(cmd));
				free(cmd);
			}
			if (buffer[j + 1] != '\0')
			{
				if (ft_check_double_symbols(&buffer[j], &cmd) == 2)
					j++;
				if (!cmd)
					return (-1);
				add_to_lst(lst, create_cmd_node(cmd));
				j++;
			}
			free(cmd);
			len = 0;
		}
		len++;
		j++;
	}
	ft_split_cmd(lst);
	return (0);
}
