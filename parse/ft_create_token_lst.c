#include "../minishell.h"

int	ft_var_len(char *s, int brace_flag)
{
	int	i;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if ((brace_flag && s[i] != '}') || (brace_flag && i == 0))
		ft_putstr_cmd_fd("minishell : bad_substition $", 2, &s, 0);
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
	char	*var;
	char	*var_value;

	i = 0;
	if (s[i] == '{')
	{
		i = ft_var_len(&s[i + 1], 1);
		var = ft_strndup(&s[1], i);
		i += 2;
	}
	else
	{
		i = ft_var_len(&s[i], 0);
		var = ft_strndup(s, i);
	}
	var_value = ft_search_var(var, &(t_struct->envp));
	ft_replace_var(cmd, cmd_index, var_value, t_struct);
	free(var);
	return (i);
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
		else if (s[i] == '$' && c != '\'' && (ft_isalnum(s[i + 1]) || s[i
			+ 1] == '{' || s[i + 1] == '_'))
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
				&(t_struct->envp), len));
	ft_safe_malloc(cmd, ft_quote_len(s, &(t_struct->envp), len));
	cmd_index = 0;
	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += ft_inside_quote(&s[i + 1], cmd, &cmd_index, t_struct);
		else if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '{' || s[i
				+ 1] == '_'))
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

t_redir	*create_redir_node(char *s)
{
	t_redir	*new_node;

	if (!s)
		return (NULL);
	new_node = malloc(sizeof(t_redir));
	new_node->redir = ft_strdup(s);
	if (!ft_strcmp(s, "<<"))
		new_node->type = R_HEREDOC;
	else if (!ft_strcmp(s, "<"))
		new_node->type = R_IN;
	else if (!ft_strcmp(s, ">"))
		new_node->type = R_OUT;
	else if (!ft_strcmp(s, ">>"))
	{
		new_node->type = R_APPEND;
	}
	else
		new_node->type = WORD;
	new_node->next = NULL;
	return (new_node);
}

void	add_to_redir_lst(t_redir **head, t_redir *new_node)
{
	t_redir	*last;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = lst_last_redir(*head);
	last->next = new_node;
}

static int	ft_get_symb(save_struct *t_struct, char *buff, char **cmd)
{
	int		len;
	int		i;
	int		j;
	t_cmd	*last;

	last = lst_last(t_struct->cmd);
	len = 0;
	if (ft_is_symb(buff, "><"))
	{
		while (buff[len] && !ft_is_symb(&buff[len], "|()& "))
		{
			while (buff[len] && ft_is_symb(&buff[len], " ")
				&& !ft_is_symb(&buff[len], "><"))
				len++;
			j = 0;
			if (ft_is_symb(&buff[len], "><"))
			{
				j = ft_check_double_symbols(&buff[len], cmd);
				add_to_redir_lst((&last->redir), create_redir_node(*cmd));
			}
			else
			{
				while (buff[len + j] && !ft_is_symb(&buff[len + j], "|><()& "))
					j++;
				*cmd = ft_strndup(&buff[len], j);
				add_to_redir_lst((&last->redir), create_redir_node(*cmd));
			}
			free(*cmd);
			len += j;
		}
	}
	else
	{
		len = ft_check_double_symbols(buff, cmd);
		add_to_lst(&(t_struct->cmd), create_cmd_node(*cmd, buff[-1]));
		i = len;
		while (i--)
			strcat(t_struct->save_spaces, "0");
	}
	return (len);
}

void	ft_create_token_lst(char *buffer, save_struct *t_struct)
{
	char	*cmd;
	int		j;
	int		len;
	int		quote_flag;

	j = 0;
	quote_flag = -1;
	while (buffer[j])
	{
		cmd = NULL;
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
		add_to_lst(&(t_struct->cmd), create_cmd_node(cmd, buffer[j - 1]));
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(t_struct, &buffer[j], &cmd);
	}
}
