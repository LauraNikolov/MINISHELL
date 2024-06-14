#include "../minishell.h"

int	ft_changepwd_var(t_envp **env, char *old_pwd, char *pwd)
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
	printf("OLDPWD->value = %s\n", ft_search_var("OLDPWD", env));
	printf("PWD->value = %s\n",  ft_search_var("PWD", env));
	return (0);
}

int	ft_cd(save_struct *t_struct)
{
	char	*old_pwd;
	char	*path;
	char	pwd[PATH_MAX];

	// if (path[2])
	// {
	// 	ft_putstr_cmd_fd("minishell : cd: too many arguments", 2, NULL, 0);
	// 	return (ft_return_code("1", &t_struct->envp));
	// }
	old_pwd = ft_search_var("PWD", &t_struct->envp);
	path = t_struct->cmd->cmd[1];
	if (!chdir(path))
	{
		// dprintf(2, "AVANT le SWAP :\n");
		// dprintf(2, "OLD === %p\n", ft_search_var("OLDPWD", &t_struct->envp));
		// dprintf(2, "NEW === %p\n", ft_search_var("PWD", &t_struct->envp));
		getcwd(pwd, PATH_MAX);
	
		ft_changepwd_var(&t_struct->envp, old_pwd, pwd);
		// dprintf(2, "AFTER le SWAP :\n");
		// dprintf(2, "OLD === %p\n", ft_search_var("OLDPWD", &t_struct->envp));
		// dprintf(2, "NEW === %p\n", ft_search_var("PWD", &t_struct->envp));
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
