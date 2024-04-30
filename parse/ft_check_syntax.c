#include "../minishell.h"

static int	ft_check_syntax_2(t_cmd *node)
{
	if (node->type == WORD && (node->prev->type == AND
			|| node->prev->type == WORD || node->prev->type == O_BRACKET
			|| node->prev->type == OR || node->prev->type == PIPE)
		&& (node->next->type == AND || node->next->type == WORD
			|| node->next->type == O_BRACKET || node->next->type == OR
			|| node->next->type == PIPE || node->next->cmd[0][0] == '\0'))
		return (0);
	else if (node->type == O_BRACKET && (node->prev->type == AND
			|| node->prev->type == OR || node->prev->type == O_BRACKET)
		&& (node->next->type == R_OUT || node->next->type == R_IN
			|| node->next->type == R_APPEND || node->next->type == R_HEREDOC
			|| node->next->type == WORD || node->next->type == O_BRACKET))
		return (0);
	else if (node->type == C_BRACKET && node->prev->type == WORD
		&& (node->next->type == AND || node->next->type == OR
		|| node->next->cmd[0][0] == '\0'))
		return (0);
	return (-1);
}
// RAJOUTER UN sTART ???

int	ft_check_syntax(t_cmd *node)
{
	if (!node)
		return (-1);
	if ((node->type == AND || node->type == OR) && (node->prev->type == WORD
			|| node->prev->type == C_BRACKET) && (node->next->type == R_OUT
			|| node->next->type == R_IN || node->next->type == R_APPEND
			|| node->next->type == R_HEREDOC || node->next->type == WORD
			|| node->next->type == O_BRACKET))
		return (0);
	else if (node->type == PIPE && (node->prev->type == WORD
			|| node->prev->type == C_BRACKET) && (node->next->type == R_OUT
			|| node->next->type == R_IN || node->next->type == R_APPEND
			|| node->next->type == R_HEREDOC || node->next->type == WORD))
		return (0);
	else if ((node->type == R_OUT || node->type == R_IN
			|| node->type == R_APPEND || node->type == R_HEREDOC)
		&& (node->prev->type == AND || node->prev->type == WORD
			|| node->prev->type == O_BRACKET || node->prev->type == OR
			|| node->prev->type == PIPE) && node->next->type == WORD)
		return (0);
	ft_check_syntax_2(node);
	return (-1);
}
