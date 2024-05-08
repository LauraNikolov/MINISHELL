#include "../minishell.h"

static int	ft_get_symb(t_cmd **lst, char *buff, char **cmd, int j)
{
	j = ft_check_double_symbols(&buff[j], cmd);
	if (j)
	{
		add_to_lst(lst, create_cmd_node(*cmd));
		free(*cmd);
	}
	return (j);
}

int	ft_create_token_lst(char *buffer, t_cmd **lst)
{
	char	*cmd;
	int		j;
	int		len;

	j = 0;
	while (buffer[j])
	{
		len = 0;
		while (buffer[j] && !ft_is_symb(&buffer[j], "|><()&"))
		{
			j++;
			len++;
		}
		cmd = strndup(&buffer[j - len], len);
		add_to_lst(lst, create_cmd_node(cmd));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(lst, buffer, &cmd, j);
	}
	ft_remove_null_node(lst);
	return (0);
}