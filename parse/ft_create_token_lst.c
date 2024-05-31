#include "../minishell.h"

int	ft_check_braces(char *s, int brace_flag)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] == '}')
	{
		if (!ft_isalnum(s[i]))
			ft_putstr_cmd_fd("minishell : bad_substition $", 2, s);
		i++;
	}
	if (s[i] != '}' && brace_flag)
		ft_putstr_cmd_fd("minishell : bad_substition $", 2, s);
	return (i);
}

char	*ft_search_var(char *var, t_envp **env)
{
	t_envp	*curr;

	curr = *env;
	if (!var || !*var)
		return (NULL);
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, var))
			return (curr->var_value);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_replace_var(char **cmd, int *cmd_index, char *var_value,
		save_struct *t_struct)
{
	int	i;

	i = 0;
	if (!var_value)
		return (0);
	while (var_value[i])
	{
		(*cmd)[*cmd_index] = var_value[i];
		strcat(t_struct->save_spaces, "0");
		(*cmd_index)++;
		i++;
	}
	return (0);
}

int	ft_expand(char **cmd, char *s, int *cmd_index, save_struct *t_struct)
{
	int		i;
	char	*var = NULL;
	char	*var_value;

	i = 0;
	if (s[i] == '{')
	{
		i = ft_check_braces(&s[i], 1);
		var = ft_strndup(&s[1], i);
		i++;
	}
	else
	{
		while (s[i] && (ft_isalnum(s[i]) || (s[i] == '_')))
			i++;
		var = ft_strndup(s, i);
	}
	var_value = ft_search_var(var, &(t_struct->envp));
	ft_replace_var(cmd, cmd_index, var_value, t_struct);
	free(var);
	return (i + 1);
}

int	ft_inside_quote(char *s, char **cmd, int *cmd_index, save_struct *t_struct)
{
	int		i;
	char	c;

	c = s[-1];
	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			strcat(t_struct->save_spaces, "1");
			(*cmd_index)++;
		}
		else if (s[i] == '$' && c != '\'')
			i += ft_expand(cmd, &s[i + 1], cmd_index, t_struct);
		else
		{
			(*cmd)[*cmd_index] = s[i];
			strcat(t_struct->save_spaces, "0");
			(*cmd_index)++;
		}
		i++;
	}
	return (i + 1);
}

int	ft_handle_quote(char *s, char **cmd, int len, save_struct *t_struct)
{
	int	i;
	int	cmd_index;

	if (!t_struct->save_spaces)
		ft_safe_malloc(&(t_struct->save_spaces), ft_quote_len(s,
				&(t_struct->envp)));
	ft_safe_malloc(cmd, ft_quote_len(s, &(t_struct->envp)));
	cmd_index = 0;
	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += ft_inside_quote(&s[i + 1], cmd, &cmd_index, t_struct);
		else if (s[i] == '$')
			i += ft_expand(cmd, &s[i + 1], &cmd_index, t_struct);
		else
		{
			(*cmd)[cmd_index] = s[i];
			if ((*cmd)[cmd_index] != ' ')
				strcat(t_struct->save_spaces, "3");
			else
				strcat(t_struct->save_spaces, "2");
			cmd_index++;
		}
		i++;
	}
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

static int	ft_get_symb(save_struct *t_struct, char *buff, char **cmd)
{
	int	i;
	int	j;
	int	len;

	i = ft_check_double_symbols(buff, cmd);
	len = 0;
	j = 0;
	if (buff[j] && ((buff[j] == '>' && buff[j + 1] != '>') || (buff[j] == '<'
				&& buff[j + 1] != '<')))
		j = ft_add_redir(&(t_struct->cmd), &buff[i], cmd);
	else
		add_to_lst(&(t_struct->cmd), create_cmd_node(*cmd, NULL));
	free(*cmd);
	j += i;
	while (i--)
		strcat(t_struct->save_spaces, "0");
	return (len + j);
}

void	ft_create_token_lst(char *buffer, save_struct *t_struct)
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
		ft_handle_quote(&buffer[j - len], &cmd, len, t_struct);
		add_to_lst(&(t_struct->cmd), create_cmd_node(cmd, NULL));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(t_struct, &buffer[j], &cmd);
	}
	printf ("%s\n", t_struct->save_spaces);
}
