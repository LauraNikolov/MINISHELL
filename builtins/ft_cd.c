#include "../minishell.h"

static int	ft_changepwd_var(t_envp **env, char *pwd, char *old_pwd)
{
	t_envp	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "OLDPWD"))
			ft_override_content(&curr->var_value, old_pwd);
		else if (!ft_strcmp(curr->var_name, "PWD"))
			ft_override_content(&curr->var_value, pwd);
		curr = curr->next;
	}
	return (0);
}

int	ft_cd(save_struct *t_struct)
{
	char	*path;
	char 	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];

	if (t_struct->cmd->cmd[2])
	{
		ft_putstr_cmd_fd("minishell : cd: too many arguments", 2, NULL, 0);
		return (ft_return_code("1", &t_struct->envp));
	}
	path = t_struct->cmd->cmd[1];
	getcwd(old_pwd, PATH_MAX);
	if (!chdir(path))
	{
		getcwd(pwd, PATH_MAX);
		ft_changepwd_var(&t_struct->envp, pwd , old_pwd);
	}
	else
		return (ft_return_code("1", &t_struct->envp));
	return (ft_return_code("0", &t_struct->envp), 0);
}
/*

char	*curr_folder = NULL;
int		nb;


if (!strcmp(path))

nb = ft_count_slash(path);
if (nb)
{
	ft_find_new_dir(old_pwd, nb);
}
exit(0);

printf("path = %s\n", path);
// if (getcwd(pwd, PATH_MAX))
curr_folder = ft_strdup(&pwd[ft_strrchr(pwd, '/') + 1]);
// printf("curr_folder = %s\n", curr_folder);

free(curr_folder);
// free(new_folder); */
