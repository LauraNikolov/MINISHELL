#include "../minishell.h"

static void	ft_echo_str(char **cmd, int option)
{
	int	i;

	i = 0;
	while (cmd[++i])
		ft_putstr_fd(cmd[i], 1);
	if (option)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(char **cmd)
{
	if (!cmd[1])
		return (0);
	int i = 1;

	if (cmd[1][0] == '-' && cmd[1][0] == 'n')
	{
		while (cmd[1][i])
		{
			if (cmd[1][i] != 'n')
			{
				ft_echo_str(cmd, 0);
				return (0);
			}
			i++;
		}
	}
	ft_echo_str(cmd, 1);
	return (0);
}