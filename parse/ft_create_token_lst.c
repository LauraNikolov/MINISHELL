#include "../minishell.h"

int	ft_check_braces(char *s, char **save_spaces)
{
	int	counter;
	int	i;

	(void)save_spaces;
	i = 0;
	counter = 0;
	while (s[i] && s[i] == '{')
	{
		counter++;
		i++;
	}
	while (s[i] && s[i] != '}')
		i++;
	while (s[i] && s[i] == '}')
	{
		counter++;
		i++;
	}
	if (counter != 2)
		ft_putstr_cmd_fd("bad_substition", 2, NULL);
	return (i - counter);
}

char	*ft_search_var(char *var, t_envp **env)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, var))
			return (curr->var_value);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_expand(char **cmd, char *s, char c, save_struct *t_struct)
{
	int		i;
	char	*var;

	(void)cmd;
	var = NULL;
	i = 0;
	if (c == '\'')
		return (0);
	else
	{
		i = 1;
		if (s[i] == '{')
		{
			i = ft_check_braces(&s[i], &(t_struct->save_spaces));
			var = ft_strndup(&s[1], i);
		}
		else
		{
			while (s[i] && s[i] != ' ' && s[i] != c)
				i++;
			var = ft_strndup(&s[1], i - 1);
			printf("%s\n", ft_search_var(var, &(t_struct->envp)));
		}
	}
	free(var);
	return (0);
}

int	ft_inside_quote(char *s, char **cmd, int *cmd_index, save_struct *t_struct)
{
	int		i;
	char	c;

	c = s[0];
	i = 1;
	while (s[i] && s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			strcat(t_struct->save_spaces, "1");
			(*cmd_index)++;
			i++;
			continue ;
		}
		if (s[i] == '$')
			*cmd_index += ft_expand(cmd, &s[i], c, t_struct);
		(*cmd)[*cmd_index] = s[i];
		strcat(t_struct->save_spaces, "0");
		(*cmd_index)++;
		i++;
	}
	(*cmd)[*cmd_index] = '\0';
	return (i + 1);
}

int	ft_handle_quote(char *s, char **cmd, int len, save_struct *t_struct)
{
	int	i;
	int	cmd_index;

	if (!t_struct->save_spaces)
		ft_safe_malloc(&(t_struct->save_spaces), ft_quote_len(s, &(t_struct->envp) + 1));
	ft_safe_malloc(cmd, ft_quote_len(s, &(t_struct->envp) + 1));
	cmd_index = 0;
	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += ft_inside_quote(&s[i], cmd, &cmd_index, t_struct);
		else
		{
			(*cmd)[cmd_index] = s[i];
			if ((*cmd)[cmd_index] != ' ')
				strcat(t_struct->save_spaces, "3");
			else
				strcat(t_struct->save_spaces, "2");
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
	printf("savespaces %s\n", t_struct->save_spaces);
}
