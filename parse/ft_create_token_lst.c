#include "../minishell.h"

int	ft_inside_quote(char *s, char **cmd, char c, int *cmd_index,
		char **save_spaces)
{
	int	i;

	i = 1;
	while (s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			strcat(*save_spaces, "1");
			(*cmd_index)++;
			i++;
			continue ;
		}
		(*cmd)[*cmd_index] = s[i];
		strcat(*save_spaces, "0");
		(*cmd_index)++;
		i++;
	}
	(*cmd)[*cmd_index] = '\0';
	return (i + 1);
}

int	ft_handle_quote(char *s, char **cmd, int len, char **save_spaces)
{
	int	i;
	int	cmd_index;

	if (!*save_spaces)
		ft_safe_malloc(save_spaces, ft_quote_len(s) + 1);
	ft_safe_malloc(cmd, ft_quote_len(s) + 1);
	cmd_index = 0;
	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += ft_inside_quote(&s[i], cmd, s[i], &cmd_index, save_spaces);
		else
		{
			(*cmd)[cmd_index] = s[i];
			if ((*cmd)[cmd_index] != ' ')
				strcat(*save_spaces, "3"); // change fonctions
			else
				strcat(*save_spaces, "2");
			cmd_index++;
			i++;
		}
	}
	(*cmd)[cmd_index] = '\0';
	return (i);
}

static int	ft_add_redir(t_cmd **lst, char *buff, char **cmd)
{
	int	spaces;
	int	len;
	int	i;

	len = 0;
	i = 0;
	spaces = 0;
	while (buff[i] && buff[i] == ' ')
	{
		spaces++;
		i++;
	}
	while (buff[i] && (buff[i] != ' ' || buff[i] == '\0'))
	{
		len++;
		i++;
	}
	add_to_lst(lst, create_cmd_node(*cmd, ft_strndup(&buff[spaces + 1], len
				+ 1)));
	return (i);
}

static int	ft_get_symb(t_cmd **lst, char *buff, char **cmd, char **save_spaces)
{
	int	i;
	int	j;
	int	len;

	i = ft_check_double_symbols(buff, cmd);
	len = 0;
	j = 0;
	if (buff[j] && ((buff[j] == '>' && buff[j + 1] != '>') || (buff[j] == '<'
				&& buff[j + 1] != '<')))
		j = ft_add_redir(lst, &buff[i], cmd);
	else
		add_to_lst(lst, create_cmd_node(*cmd, NULL));
	free(*cmd);
	j += i;
	while (i--)
		strcat(*save_spaces, "0");
	return (len + j);
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
		add_to_lst(lst, create_cmd_node(cmd, NULL));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(lst, &buffer[j], &cmd, save_spaces);
	}
}
