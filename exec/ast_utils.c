#include "../minishell.h"

int ft_check_bracket(t_ast *token)
{
	t_ast	*tmp_prev;
	int		i;

	if (!token || !token->prev)
		return (0);
	tmp_prev = token->prev;
	i = 0;
	while (tmp_prev)
	{
		if (tmp_prev->type == O_BRACKET)
			i++;
		else if (tmp_prev->type == C_BRACKET)
			i--;
		tmp_prev = tmp_prev->prev;
	}
	return (i);
}

void ft_clear_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	ft_clear_ast(root->left);
	ft_clear_ast(root->right);
	free(root);
}

t_ast	*ast_init(void)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->token = NULL;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_ast	*ast_new_node(t_token *token)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->token = token;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_ast	*create_operator_node(t_token *token, t_ast *left, t_ast *right)
{
	t_ast *node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	node->left = left;
	node->right = right;
	return (node);
}