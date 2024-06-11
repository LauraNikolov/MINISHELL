#include "../minishell.h"

static t_ast	*ft_check_logic_op(t_ast *current, t_ast *root)
{
	if (current->type == AND || current->type == OR)
	{
		if (!root || ft_check_bracket(root) > ft_check_bracket(current))
			root = current;
	}
	return (root);
}

static t_ast	*ft_find_root(t_ast *first, t_ast *last)
{
	t_ast	*current;
	t_ast	*root;

	current = last;
	root = NULL;
	while (current && current != first)
	{
		root = ft_check_logic_op(current, root);
		current = current->prev;
	}
	if (!root)
	{
		current = last;
		while (current && current != first)
		{
			if (current->type == PIPE)
			{
				root = current;
				break ;
			}
			current = current->prev;
		}
	}
	return (root);
}

static t_ast	*ft_create_cmd_node(t_ast *ast)
{
	while (ast->type == O_BRACKET)
		ast = ast->next;
	return (ast_new_node(ast));
}

static t_ast	*ft_create_subtree(t_ast *first, t_ast *last, t_ast *root)
{
	t_ast	*left_hand;
	t_ast	*right_hand;
	t_ast	*left;
	t_ast	*right;

	left_hand = root->prev;
	right_hand = root->next;
	left = create_ast(first, left_hand);
	right = create_ast(right_hand, last);
	return (create_operator_node(root, left, right));
}

t_ast	*create_ast(t_ast *first, t_ast *last)
{
	t_ast *root;

	root = ft_find_root(first, last);
	if (!root)
		return (ft_create_cmd_node(first));
	else
		return (ft_create_subtree(first, last, root));
}