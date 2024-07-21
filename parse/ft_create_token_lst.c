#include "../minishell.h"

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
	int	len;
	int	i;

	i = 0;
	len = ft_check_double_symbols(buff, cmd);
	add_to_lst(&(t_struct->cmd), create_cmd_node(NULL, cmd, buff[-1]));
	i = len;
	while (i--)
		ft_strcat(t_struct->save_spaces, "0");
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
	cmd = NULL;
	while (buffer[j])
	{
		len = 0;
		while (((buffer[j] && quote_flag == 1)) || ((buffer[j]
					&& !ft_is_str(buffer[j], "|()&") && quote_flag == -1)))
		{
			if (buffer[j] == '\'' || buffer[j] == '\"')
				quote_flag *= -1;
			j++;
			len++;
		}
		printf("%c\n", buffer[j]);
		add_to_lst(&(t_struct->cmd), create_cmd_node(ft_handle_quote(&buffer[j
					- len], &cmd, len, t_struct, ft_strlen(buffer)), &cmd, buffer[j - 1]));
		if (ft_is_str(buffer[j], "|()&"))
			j += ft_get_symb(t_struct, &buffer[j], &cmd);
	}
}

