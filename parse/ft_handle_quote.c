#include "../minishell.h"

static void    ft_encode_spaces(save_struct *t_struct, char **cmd, int *cmd_index, char c)
{
    if (*cmd)
        (*cmd)[*cmd_index] = c;
    if (!t_struct)
        return ;
    if ((*cmd)[*cmd_index] != ' ')
		ft_strcat(t_struct->save_spaces, "3");
	else
        ft_strcat(t_struct->save_spaces, "2");
}

int	ft_quote_len(char *s, int len)
{
	int		i;
	int		var_size;
	int		quote_flag;
	int		quote_len;
	char	c;

	quote_flag = -1;
	var_size = 0;
	i = -1;
	quote_len = 0;
	c = '\0';
	while (s[++i] && i < len)
	{
		if ((quote_flag == -1 && s[i] == '\"') || (quote_flag == -1
				&& s[i] == '\'') || (s[i] == c))
		{
			quote_flag *= -1;
			c = s[i];
			quote_len++;
		}
	}
	if (quote_len % 2 != 0)
		return (-1);
	return (i + var_size - quote_len);
}

t_redir	*ft_handle_quote(char *s, char **cmd, int len, save_struct *t_struct, int bufflen)
{
	int		i;
	int		cmd_index;
	t_redir	*redir;

	redir = NULL;
	if (t_struct && !t_struct->save_spaces)
		ft_safe_malloc(&(t_struct->save_spaces), bufflen + 1);
	ft_safe_malloc(cmd, ft_quote_len(s, len) + 1);
	cmd_index = 0;
	i = -1;
	while (s[++i] && i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += ft_inside_quote(&s[i + 1], cmd, &cmd_index, t_struct);
		else if (ft_is_str(s[i], "><"))
			add_to_redir_lst(&redir, ft_redir(s, &i, len));
		else
		{
            ft_encode_spaces(t_struct, cmd, &cmd_index, s[i]);
			cmd_index++;
		}
	}
	return (redir);
}

int	ft_inside_quote(char *s, char **cmd, int *cmd_index, save_struct *t_struct)
{
	int		i;
	char	c;

	i = 0;
	c = s[-1];
	printf("s = %s\n", s);
	while (s[i] && s[i] != c)
	{
		if (s[i] == ' ')
		{
			(*cmd)[*cmd_index] = '%';
			if(t_struct)
				ft_strcat(t_struct->save_spaces, "1");
			(*cmd_index)++;
		}
		else
		{
			(*cmd)[*cmd_index] = s[i];
			if (t_struct)
				ft_strcat(t_struct->save_spaces, "0");
			(*cmd_index)++;
		}
		i++;
	}
	printf("s[i] = %s\n", &s[i]);
	return (i + 1);
}