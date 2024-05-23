#include "../minishell.h"

int	ft_check_pipe(t_cmd *node)
{
	if (!node->prev || !node->next)
	{
		printf("syntax error near unexpected token '%s'\n", node->cmd[0]);
		return (-1);
	}
	if (!(node->prev->type == WORD || node->prev->type == C_BRACKET)
		&& (node->next->type == R_OUT || node->next->type == R_IN
			|| node->next->type == R_APPEND || node->next->type == R_HEREDOC
			|| node->next->type == WORD))
	{
		printf("syntax error near unexpected token '%s'\n", node->cmd[0]);
		return (-1);
		// return le code d erreur
	}
	return (0);
}

int	ft_check_word(t_cmd *node)
{
	if (node->prev && node->next)
	{
		if (node->prev->type == C_BRACKET)
			return (-2);
	}
	ft_get_path(node);
	return (0);
}

int	ft_check_Cbracket(t_cmd *node)
{
	t_cmd	*curr;

	if (!node->next)
		return (0);
	if (node->next == WORD)
		return (-1);
	curr = node;
	while (curr)
	{
		if (curr->prev == NULL)
			ft_putstr_cmd_fd("syntax error near unexpected token `", 2,
				node->cmd[0]);
		if (curr->prev->type == O_BRACKET)
			break ;
		curr = curr->prev;
	}
	return (0);
}

int	ft_is_enum(t_cmd *node)
{
	if (node->type == R_OUT)
		return (1);
	else if (node->type == O_BRACKET)
		return (1);
	else if (node->type == AND)
		return (1);
	else if (node->type == OR)
		return (1);
	else if (node->type == WORD)
		return (1);
	else
		return (0);
}

int	ft_is_enum2(t_cmd *node)
{
	if (!node)
		return (1);
	if (node->type == R_OUT)
		return (1);
	else if (node->type == AND)
		return (1);
	else if (node->type == OR)
		return (1);
	else if (node->type == C_BRACKET)
		return (1);
	else
		return (0);
}

int	ft_check_Obracket(t_cmd *node)
{
	t_cmd	*curr;
	int		p_counter;

	curr = NULL;
	p_counter = 0;
	if (*(node->bool_bracket) == 0)
	{
		curr = node;
		while (curr)
		{
			if (curr->type == O_BRACKET && ft_is_enum(curr->next))
				p_counter++;
			if (curr->type == C_BRACKET && ft_is_enum2(curr->next))
				p_counter--;
			curr = curr->next;
		}
		if (p_counter != 0)
		{
			// printf("p_counter = %d\n", p_counter);
			// printf("curr->next = %s\n", curr->cmd[0]);
			printf("Parenthesis error\n");
			exit(-1);
		}
		*(node->bool_bracket) = 1;
		printf ("good number of parenthesis\n");
		// printf("p_counter = %d\n", p_counter);
		// printf("curr->next = %s\n", curr->cmd[0]);
	}
	exit(0);
	return (0);
}

// t_cmd	*curr;
// int		i;

// if (node && *(node->bool_bracket) == 0)
// {
// 	curr = node;
// 	i = 0;
// 	while (curr && curr->type == O_BRACKET)
// 	{
// 		i++;
// 		curr = curr->next;
// 	}
// 	while (curr && curr->type != C_BRACKET && curr->type != O_BRACKET)
// 		curr = curr->next;
// 	while (curr && curr->type == C_BRACKET && curr->type != O_BRACKET)
// 	{
// 		if (curr->type == C_BRACKET)
// 			i--;
// 		curr = curr->next;
// 	}
// 	if (i != 0 || !node->next || (curr && curr->type == O_BRACKET))
// 		ft_putstr_cmd_fd("syntax error near unexpected token `", 2,
// 			node->cmd[0]);
// 	*(node->bool_bracket) = 1;
// }
// return (0);

void	ft_exec_syntax_functions(t_cmd **cmd, int (*ft_tab[9])(t_cmd *))
{
	t_cmd	*curr;

	curr = *cmd;
	while (curr)
	{
		// while (curr && ft_tab[curr->type] == NULL)
		// 	curr = curr->next;
		ft_tab[curr->type](curr);
		curr = curr->next;
	}
}

int	ft_init_ft_tab(int (*ft_tab[9])(t_cmd *))
{
	ft_tab[WORD] = ft_check_word;
	ft_tab[PIPE] = ft_check_pipe;
	ft_tab[AND] = NULL;
	ft_tab[OR] = NULL;
	ft_tab[R_IN] = NULL;
	ft_tab[R_OUT] = NULL;
	ft_tab[R_APPEND] = NULL;
	ft_tab[R_HEREDOC] = NULL;
	ft_tab[O_BRACKET] = ft_check_Obracket;
	ft_tab[C_BRACKET] = ft_check_Cbracket;
	return (0);
}