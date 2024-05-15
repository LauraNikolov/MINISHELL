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
			(*save_spaces)[*cmd_index] = '1';
			(*cmd_index)++;
			i++;
			continue ;
		}
		(*cmd)[*cmd_index] = s[i];
		(*save_spaces)[*cmd_index] = '0';
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

	i = 1;
	while (s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			(*save_spaces)[*cmd_index] = '1';
			(*cmd_index)++;
			i++;
			continue ;
		}
		(*cmd)[*cmd_index] = s[i];
		(*save_spaces)[*cmd_index] = '0';
		(*cmd_index)++;
		i++;
	}
	(*cmd)[*cmd_index] = '\0';
	return (i + 1);
}

int	ft_handle_quote(char *s, char **cmd)
{
	int		i;
	int		cmd_index;
	int		quote_status;
	char	*save_spaces;

	cmd_index = 0;
	quote_status = 0;
	save_spaces = ft_calloc(ft_quote_len(s) + 1, sizeof(char));
	if (!save_spaces)
		return (0);
	*cmd = malloc(sizeof(char) * ft_quote_len(s) + 1);
	if (!cmd)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i += ft_simple_quote(&s[i], cmd, s[i], &cmd_index, &save_spaces);
		else if (s[i] == '\"')
			i += ft_double_quote(&s[i], cmd, s[i], &cmd_index, &save_spaces);
		else
		{
			(*cmd)[cmd_index] = s[i];
			save_spaces[cmd_index] = '0';
			cmd_index++;
			i++;
		}
	}
	(*cmd)[cmd_index] = '\0';
	save_spaces[cmd_index] = '\0';
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
	int		quote_flag;

	j = 0;
	cmd = NULL;
	quote_flag = -1;
	while (buffer[j])
	{
		len = 0;
		while ((buffer[j] && !ft_is_symb(&buffer[j], "|><()&")) || (buffer[j]
				&& quote_flag == 1 && ft_is_symb(&buffer[j], "|><()&")))
		{
			if (buffer[j] == '\'' || buffer[j] == '\"')
				quote_flag *= -1;
			j++;
			len++;
		}
		// printf("len = %d\n", len);
		ft_handle_quote(buffer, &cmd);
		add_to_lst(lst, create_cmd_node(cmd));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(lst, buffer, &cmd, j);
	}
	ft_remove_null_node(lst);
	return (0);
}
