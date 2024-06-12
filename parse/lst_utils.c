#include "../minishell.h"

int	ft_lst_size(t_cmd *cmd)
{
	t_cmd	*save;
	int		i;

	i = 0;
	save = cmd;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	cmd = save;
	return (i);
}

void	ft_free_envp_lst(t_envp **lst)
{
	t_envp	*curr;
	t_envp	*temp;

	curr = *lst;
	while (curr)
	{
		temp = curr->next;
		free(curr->var_name);
		free(curr->var_value);
		free(curr);
		curr = temp;
	}
	*lst = NULL;
}

void	ft_free_node(t_cmd *node)
{
	int	i;

	i = 0;
	while (node->cmd[i])
	{
		free(node->cmd[i]);
		i++;
	}
	free(node->cmd);
	free(node->path);
	free(node);
}
void	ft_free_lst(t_cmd *lst)
{
	t_cmd	*temp;

	while (lst)
	{
		temp = lst->next;
		ft_free_node(lst);
		lst = temp;
	}
}

int	ft_print_envp(t_envp **envp)
{
	t_envp	*curr;

	curr = *envp;
	while (curr)
	{
		if (!ft_strcmp(curr->var_name, "?"))
		{
			curr = curr->next;
			continue ;
		}
		printf("%s", curr->var_name);
		printf("=%s\n", curr->var_value);
		curr = curr->next;
	}
	return (ft_return_code(0, envp));
}

void	ft_print_lst(t_cmd *node)
{
	t_cmd	*curr;
	int		i;
	int		command_num;

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
		printf("redir = %s\n", curr->redir);
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
		new_node->prev = NULL;
		return ;
	}
	last = lst_envp_last(*head);
	new_node->prev = last;
	last->next = new_node;
}
t_envp	*create_envp_node(char *var_name)
{
	t_envp	*envp;
	int		i;

	envp = malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);
	i = 0;
	if (ft_is_char(var_name, '='))
	{
		while (var_name[i] && var_name[i] != '=')
			i++;
		envp->var_name = ft_strndup(var_name, i);
		envp->var_value = ft_strdup(&var_name[i + 1]);
	}
	else
	{
		envp->var_name = ft_strndup(var_name, i);
		envp->var_value = NULL;
	}
	envp->next = NULL;
	envp->prev = NULL;
	return (envp);
}

t_cmd	*create_cmd_node2(t_cmd *new_node, char *cmd)
{
	if (!ft_strcmp(cmd, ">>"))
		new_node->type = R_APPEND;
	else if (!ft_strcmp(cmd, "||"))
		new_node->type = OR;
	else if (!ft_strcmp(cmd, "&&"))
		new_node->type = AND;
	else if (!ft_strcmp(cmd, "&"))
		new_node->type = NO_TYPE;
	else if (!ft_strcmp(cmd, "("))
		new_node->type = O_BRACKET;
	else if (!ft_strcmp(cmd, ")"))
		new_node->type = C_BRACKET;
	else
		new_node->type = WORD;
	free(cmd);
	return (new_node);
}

t_cmd	*create_cmd_node(char *cmd, char *redir, char c)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_split(cmd, " ");
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->path = NULL;
	new_node->bool_bracket = NULL;
	new_node->redir = redir;
	new_node->expand_flag = 0;
	if (c != '\'')
		new_node->expand_flag = 1;
	if (!ft_strcmp(cmd, "|"))
		new_node->type = PIPE;
	else if (!ft_strcmp(cmd, "<<"))
		new_node->type = R_HEREDOC;
	else if (!ft_strcmp(cmd, "<"))
		new_node->type = R_IN;
	else if (!ft_strcmp(cmd, ">"))
		new_node->type = R_OUT;
	return (create_cmd_node2(new_node, cmd));
}
