#include "../minishell.h"

void	ft_free_lst(t_cmd *lst)
{
	t_cmd	*curr;
	t_cmd	*temp;

	curr = lst;
	while (curr)
	{
		temp = curr->next;
		ft_free_tab(curr->cmd);
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
		curr->cmd = ft_strdup_array(split_cmd);
		ft_free_tab(split_cmd);
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
			printf("COMMAND\n");
		else if (curr->type == 1)
			printf("PIPE\n");
		else if (curr->type == 2)
			printf("AND\n");
		else if (curr->type == 3)
			printf("OR\n");
		else if (curr->type == 4)
			printf("REDIR\n");
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

void	add_to_lst(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*last;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = lst_last(*head);
	last->next = new_node;
}

t_cmd	*create_node(char **cmd)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	// printf("Adresse de la variable pointée : %p\n", &(*(*cmd)));
	// printf(" Contenu du double pointeur: %p\n", *cmd);
	new_node->cmd = ft_strdup_array(cmd);
	new_node->next = NULL;
	new_node->path = NULL;
	if (ft_str_is_alpha(cmd[0]))
		new_node->type = COMMAND;
	else if (!ft_strcmp(cmd[0], "|"))
		new_node->type = PIPE;
	else if (!ft_strcmp(cmd[0], ">") || !ft_strcmp(cmd[0], "<")
		|| !ft_strcmp(cmd[0], ">>") || !ft_strcmp(cmd[0], "<<"))
		new_node->type = REDIR;
	else if (!ft_strcmp(cmd[0], "||"))
		new_node->type = OR;
	else if (!ft_strcmp(cmd[0], "&&"))
		new_node->type = AND;
	else if(!ft_strcmp(cmd[0], "("))
		new_node->type = PRIOR;
	else if(!ft_strcmp(cmd[0], ")"))
		new_node->type = PRIOR;
	return (new_node);
}
