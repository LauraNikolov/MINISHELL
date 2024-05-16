#include "../minishell.h"

int	ft_simple_quote(char *s, char **cmd, char c, int *cmd_index,
		char **save_spaces)
{
	int	i;

	i = 1;
	while (s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			(*save_spaces)[*cmd_index + ft_strlen(*save_spaces)] = '1';
			(*cmd_index)++;
			i++;
			continue ;
		}
		(*cmd)[*cmd_index] = s[i];
		(*save_spaces)[*cmd_index + ft_strlen(*save_spaces)] = '0';
		(*cmd_index)++;
		i++;
	}
	(*cmd)[*cmd_index] = '\0';
	return (i + 1);
}

int	ft_double_quote(char *s, char **cmd, char c, int *cmd_index,
		char **save_spaces)
{
	int	i;
	int	j;

	j = ft_strlen(*save_spaces);
	i = 1;
	while (s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			(*save_spaces)[j] = '1';
			(*cmd_index)++;
			i++;
			j++;
			continue ;
		}
		(*cmd)[*cmd_index] = s[i];
		(*save_spaces)[j] = '0';
		(*cmd_index)++;
		i++;
		j++;
	}
	(*cmd)[*cmd_index] = '\0';
	return (i + 1);
}

int	ft_handle_quote(char *s, char **cmd, int len, char **save_spaces)
{
	int	i;
	int	j;
	int	cmd_index;
	int	quote_status;

	if (!*save_spaces)
		*save_spaces = ft_calloc(ft_quote_len(s) + 1, sizeof(char));
	if (!*save_spaces)
		return (0);
	j = ft_strlen(*save_spaces);
	cmd_index = 0;
	quote_status = 0;
	*cmd = malloc(sizeof(char) * ft_quote_len(s) + 1);
	if (!cmd)
		return (0);
	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] == '\'')
			i += ft_simple_quote(&s[i], cmd, s[i], &cmd_index,
					&save_spaces[ft_strlen(*save_spaces)]);
		else if (s[i] == '\"')
			i += ft_double_quote(&s[i], cmd, s[i], &cmd_index, save_spaces);
		else
		{
			(*cmd)[cmd_index] = s[i];
			(*save_spaces)[j] = '2';
			cmd_index++;
			i++;
			j++;
		}
	}
	(*cmd)[cmd_index] = '\0';
	(*save_spaces)[cmd_index] = '\0';
	printf("%s\n", *save_spaces);
	return (i);
}

static int	ft_get_symb(t_cmd **lst, char *buff, char **cmd, int j)
{
	j = ft_check_double_symbols(&buff[j], cmd);
	add_to_lst(lst, create_cmd_node(*cmd));
	free(*cmd);
	return (j);
}

void	ft_create_token_lst(char *buffer, t_cmd **lst, char **save_spaces)
{
	char	*cmd;
	int		j;
	int		len;
	int		quote_flag;

	j = 0;
	cmd = NULL;
	quote_flag = -1;
	while (buffer[j])
	{
		len = 0;
		while (((buffer[j] && quote_flag == 1)) || ((buffer[j]
					&& !ft_is_symb(&buffer[j], "|><()&") && quote_flag == -1)))
		{
			if (buffer[j] == '\'' || buffer[j] == '\"')
				quote_flag *= -1;
			j++;
			len++;
		}
		ft_handle_quote(&buffer[j - len], &cmd, len, save_spaces);
		add_to_lst(lst, create_cmd_node(cmd));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(lst, buffer, &cmd, j);
	}
}
