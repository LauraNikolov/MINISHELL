/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:30 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/30 15:55:34 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_cmd(t_ast *root, t_exec *exec)
{
    
}


int ft_pipe(t_ast *root, t_exec *exec)
{
    
}

int exec_ast_recursive(t_ast *root, t_exec *exec)
{
    
    if(!root)
        return(0);
    if(root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        exec_ast_recursive(root->left, prev_fd, return_value, envp);
    if(root->right->cmd->type == PIPE || root->right->cmd->type == AND || root->right->cmd->type == OR)
        exec_ast_recursive(root->right, prev_fd, return_value, envp);
    ft_exec_tree(root);
    if(root->cmd->type == PIPE)
        ft_pipe(root, exec);
    return(return_value);                                                                                                                                                                                                                                                                                                                                                                        
}

/*
* une fonction qui execute une commande simple : 
* une fonction qui set le pipe
* une fonction qui set le AND
* une fonction qui set le OR
* une fonction qui gere les enfants
* une fonction qui gere le parent
*/

