/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:56:00 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/18 11:32:13 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_ast(save_struct *t_struct)
{
    //t_ast *save_ast = t_struct->ast;
    recursive_free_ast(t_struct->ast);
}

void recursive_free_ast(t_ast *root)
{
    if(!root)
        return;
    if(root->left)
        recursive_free_ast(root->left);
    if(root->right)
        recursive_free_ast(root->right);
    free(root);
}



/* 
Pour liberer l'ast :



il faut liberer d'aord les feuilles, et ne pas oublier de set les pointeurs sur nul;



*/