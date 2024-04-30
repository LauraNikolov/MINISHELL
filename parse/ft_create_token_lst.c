#include "../minishell.h"

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
			add_to_lst(lst, create_cmd_node(&cmd));
			free(cmd);
			cmd = NULL;
			if (buffer[j + 1] != '\0')
			{
				cmd = ft_strndup(&buffer[j], 1);
				if (!cmd)
					return (-1);
				add_to_lst(lst, create_cmd_node(&cmd));
				j++;
			}
			free(cmd);
			cmd = NULL;
			len = 0;
		}
		len++;
		j++;
	}
	ft_split_cmd(lst);
	return (0);
}
