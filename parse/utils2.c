#include "../minishell.h"

void	ft_all_free(save_struct *t_struct)
{
	ft_free_lst(t_struct->cmd);
	free(t_struct->save_spaces);
	free(t_struct);
}

void ft_safe_free(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

int	ft_safe_malloc(char **s, int size)
{
	if (!s)
		return (0);
	*s = ft_calloc(size, sizeof(char));
	if (!*s)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_putstr_cmd_fd (char *s, int fd, char **str, int flag)
{
	int	i;

	i = -1;
	if (flag == 2)
	{
		write(fd, s, ft_strlen(s));
		return (-1);
	}
	write(fd, s, ft_strlen(s));
	if (flag == 1)
		while (str[++i])
		{
			write(fd, " ", 2);
			ft_putstr_fd(str[i], fd);
		}
	else if (str)
	{
		ft_putstr_fd(*str, fd);
		write(fd, "\'", 2);
	}
	write(fd, "\n", 2);
	return (-1);
}