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
	if (!node->prev || !node->next)
		return (-1);
	if (node->type == WORD && (node->prev->type == AND
			|| node->prev->type == WORD || node->prev->type == O_BRACKET
			|| node->prev->type == OR || node->prev->type == PIPE)
		&& (node->next->type == AND || node->next->type == WORD
			|| node->next->type == O_BRACKET || node->next->type == OR
			|| node->next->type == PIPE))
		return (-1);
	node->path = ft_get
	return (0);
	// appel a la fonction get_path ?
	// faire une fonction qui interprete en renvoit le bon code d erreur
}

int	ft_init_ft_tab(int (*ft_tab[9])(t_cmd *))
{
	ft_tab[0] = ft_check_word;
	ft_tab[1] = ft_check_pipe;
	ft_tab[2] = NULL;
	ft_tab[3] = NULL;
	ft_tab[4] = NULL;
	ft_tab[5] = NULL;
	ft_tab[6] = NULL;
	ft_tab[7] = NULL;
	ft_tab[8] = NULL;
	ft_tab[9] = NULL;
	return (0);
}