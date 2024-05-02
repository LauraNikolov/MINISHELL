#include "../minishell.h"

void	ft_free_envp_lst(t_envp *lst)
{
	t_envp	*curr;
	t_envp	*temp;

	curr = lst;
	while (curr)
	{
		temp = curr->next;
		free(curr->var_name);
		free(curr->var_path);
		free(curr);
		curr = temp;
	}
}

void	ft_free_lst(t_cmd *lst)
{
	t_cmd	*curr;
	t_cmd	*temp;

	curr = lst;
	while (curr)
	{
		temp = curr->next;
		ft_free_tab(curr->cmd);
		free(curr->path);
		free(curr);
		curr = temp;
	}
}

void	ft_split_cmd(t_cmd **lst)
{
	t_cmd	*curr;
	char	**split_cmd;

	curr = *lst;
	while (curr)
	{
		split_cmd = ft_split(*(curr)->cmd, " ");
		ft_free_tab(curr->cmd);
		curr->cmd = split_cmd;
		curr = curr->next;
	}
}

void	ft_print_lst(t_cmd *node)
{
	t_cmd	*curr;
	int		i;
	int		command_num;

	if (!node->cmd)
		return ;
	i = 1;
	command_num = 1;
	curr = node;
	while (curr)
	{
		printf("\nCommande n%d = %s\n", command_num, curr->cmd[0]);
		while (curr->cmd[i])
		{
			printf("Options n%d : %s\n", i, curr->cmd[i]);
			i++;
		}
		printf("Path = %s\n", curr->path);
		if (curr->type == 0)
			printf("WORD\n");
		else if (curr->type == 1)
			printf("PIPE\n");
		else if (curr->type == 2)
			printf("AND\n");
		else if (curr->type == 3)
			printf("OR\n");
		else if (curr->type == 4)
			printf("R_IN\n");
		else if (curr->type == 5)
			printf("R_OUT\n");
		else if (curr->type == 6)
			printf("R_APPEND\n");
		else if (curr->type == 7)
			printf("HEREDOC\n");
		else if (curr->type == 8)
			printf("O_BRACKET\n");
		else if (curr->type == 9)
			printf("C_BRACKET\n");
		printf("\n----\n");
		command_num++;
		curr = curr->next;
		i = 1;
	}
}

t_cmd	*lst_last(t_cmd *node)
{
	t_cmd	*curr;

	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_envp	*lst_envp_last(t_envp *node)
{
	t_envp	*curr;

	curr = node;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

void	add_to_lst(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*last;

	if (!*head)
	{
		*head = new_node;
		new_node->prev = NULL;
		return ;
	}
	last = lst_last(*head);
	new_node->prev = last;
	last->next = new_node;
}

void	add_to_envp_lst(t_envp **head, t_envp *new_node)
{
	t_envp	*last;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = lst_envp_last(*head);
	last->next = new_node;
}
t_envp	*create_envp_node(char *var_name)
{
	t_envp	*envp;
	int		i;

	envp = malloc(sizeof(t_envp));
	i = 0;
	while (var_name[i] && var_name[i] != '=')
		i++;
	envp->var_name = ft_strndup(var_name, i);
	envp->var_path = ft_strdup(&var_name[i + 1]);
	return (envp);
}
t_cmd	*create_cmd_node(char *cmd)
{
	t_cmd	*new_node;
	char **command;

	command = NULL;

	command = malloc(2 * sizeof(char *));
	command[0] = ft_strdup(cmd);
	command[1] = NULL;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = command;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->path = NULL;
	if (ft_str_is_alpha(cmd))
		new_node->type = WORD;
	else if (!ft_strcmp(cmd, "|"))
		new_node->type = PIPE;
	else if (!ft_strcmp(cmd, "<<"))
		new_node->type = R_HEREDOC;
	else if (!ft_strcmp(cmd, "<"))
		new_node->type = R_IN;
	else if (!ft_strcmp(cmd, ">"))
		new_node->type = R_OUT;
	else if (!ft_strcmp(cmd, ">>"))
		new_node->type = R_APPEND;
	else if (!ft_strcmp(cmd, "||"))
		new_node->type = OR;
	else if (!ft_strcmp(cmd, "&&"))
		new_node->type = AND;
	else if (!ft_strcmp(cmd, "("))
		new_node->type = O_BRACKET;
	else if (!ft_strcmp(cmd, ")"))
		new_node->type = C_BRACKET;
	return (new_node);
}
