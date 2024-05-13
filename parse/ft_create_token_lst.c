#include "../minishell.h"

// int ft_heaven_quote(char *buff)
// {
// 	int i;
// 	int j;
// 	int count;
// 	char c;

// 	count = 0;
// 	i = 0;
// 	while(buff[i] != '\"' && buff[i] != '\'')
// 		i++;
// 	j = ft_strrchr(&buff[i], buff[i]);
// 	c = buff[i];
// 	i++;
// 	while(i < j)
// 	{
// 		if (buff[i] == c)
// 			count++;
// 		i++;
// 	}
// 	if (count % 2 == 0)
// 		return (1);
// 	return (0);
// }

static int	ft_get_symb(t_cmd **lst, char *buff, char **cmd, int j)
{
	j = ft_check_double_symbols(&buff[j], cmd);
	add_to_lst(lst, create_cmd_node(*cmd));
	free(*cmd);
	return (j);
}

static int ft_quote_len(char *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(s[i])
	{
		while (s[i] == c)
		{
			len++;
			i++;
		}
		while (s[i] == ' ')
		{
			if (s[i] && s[i+1] != ' ')
				len--;
			len++;
			i++;
		}
		i++;
	}
	return (i - len);
}

char *ft_strdup_spaces(char *s, char c)
{
	int i;
	int j;
	char *res;

	res = malloc(sizeof(char) * (ft_quote_len(s, c) + 1));
	j = 0;
	i = 0;
	while(s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] == ' ')
			{res[j] = s[i];
			j++;}
		while (s[i] && s[i] == ' ')	
			i++;
		while (s[i] != c && s[i] != ' ')
			res[j++] = s[i++];
	}
	printf ("%d\n", j);
	res[j] = '\0';
	printf ("res = %s\n", res);
	exit(0);
	i = 0;
	while(s[i] == ' ' || s[i] == '\t')
		i++;

}

int	ft_create_token_lst(char *buffer, t_cmd **lst)
{
	char	*cmd;
	int		j;
	int		len;

	j = 0;
	cmd = NULL;
	while (buffer[j])
	{
		len = 0;
		while (buffer[j] && !ft_is_symb(&buffer[j], "|><()&"))
		{
			if (buffer[j] == '\"' || buffer[j] == '\'')
			{
				// printf("len = %d, j = %d\n", len, j);
				cmd = ft_strdup_spaces(buffer, buffer[j]);
				break ;
			}
			else
				j++;
			len++;
		}
		cmd = ft_strndup(&buffer[j - len], len);
		if (len)
			add_to_lst(lst, create_cmd_node(cmd));
		free(cmd);
		if (ft_is_symb(&buffer[j], "|><()&"))
			j += ft_get_symb(lst, buffer, &cmd, j);
	}
	ft_remove_null_node(lst);
	return (0);
}