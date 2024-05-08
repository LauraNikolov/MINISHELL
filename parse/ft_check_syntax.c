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

int	ft_check_syntax(t_cmd *node) // check if the disposition of the operator are ok
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


// <<void ft_start_state()
// {
// 	if(*nod->type == WORD)
// 		return;
// 	else
// 		ft_error(124);
	
// }

// ft_after_cmds()
// {
// 	if(nods == PIPE)
// 		ft_after_pipe()
// 		infile = open()

// 	if(nods == WORD)
// 		return;
	
// }

// void ft_command_line_state(t_cmd *node)
// {
// 	int lst_size;
// 	enum state;

// 	lst_size == 0
// 	START;
// 	AFTER_CMD;
// 	AFTER_PIPE;
// 	AFTER_AND;
// 	AFTER_OR;
// 	AFTER_REDIR;

// 	//words
// 	if(lst_size == 0)
// 		state == START;
// 		ft_start_tate(*nods)
// 	else if(nods->prev->state == WORDS)
// 		ft_after_cmd()





// 	//operateur


// 	if(node != CMD)
// 	state = node->type;
// 	lst_size = ft_lst_size(node);
// 	if(node->type )
// 	// * APRES UN MOT;
// 	// * si c'est le debut de la liste chainee, cela ne peut etre qu'une commande
// 	// * si c'est apres une commande et que c'est un word, cela ne peut etre qu'une option ou infile (a mettre dans le tableau pour execve)
// 	// * si c'est une option apres une option, le mettre dans le tableau pour execve
	
// 	// * APRES UN OPERATEUR
// 	// * 
// }>>