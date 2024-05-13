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
	// faire une fonction qui interprete en renvoit le bon code d erreur
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
	ft_tab[O_BRACKET] = NULL;
	ft_tab[C_BRACKET] = NULL;
	return (0);
}