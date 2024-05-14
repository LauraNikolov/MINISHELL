/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:45:40 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/14 18:33:11 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast *create_ast_node(t_cmd *node)
{
    t_ast *astNode;
    
    astNode = (t_ast *)malloc(sizeof(t_ast));
    astNode->type = node->type;
    astNode->left = NULL;
    astNode->right = NULL;
    astNode->parent = NULL;
    if(astNode->type == PIPE || astNode->type == AND || astNode->type == OR)
    {
        if(astNode->type == AND || astNode->type == OR)
            astNode->data.operator.prior = 2;
        else
            astNode->data.operator.prior = 1;
    }
    else
    {
        if(astNode->type == WORD)
        {
            astNode->data.command.cmds = node->cmd;
            astNode->data.command.cmd_path = node->path;
            astNode->data.command.infile = NULL;
            astNode->data.command.outfile = NULL;
            astNode->data.command.std_in = 0;
            astNode->data.command.std_out = 0;
        }
        //is_it_redir() // ! TODO
    }
    return(astNode);
}


t_ast *join_tree(t_ast *left, t_ast *right, t_ast *parent)
{
    parent->left = left;
    parent->right = right;
    left->parent = parent;
    right->parent = parent;
    return(parent);
}


void build_ast(save_struct *t_struct)
{
    t_ast *root;
    t_cmd *save;
    t_cmd *current;
    t_cmd *limiteur;
    t_ast *right;
    t_ast *left;
    
    current = t_struct->cmd;

    root = NULL;
    save = t_struct->cmd;
    // * trouver le root
    while(current->next)
        current = current->next;
    while(current != save)
    {
        if(current->type == PIPE || current->type == AND || current->type == OR)
        {
            root = create_ast_node(current);
            limiteur = current;
            break;
        }
        current = current->prev;
    }
    current = save
    // * constuire arbre gauche
    while(current)
    {



        
    }  
    // * constuire arbre droit
    while(current)
    {


        
        
    }
    // * join les arbres
    current = save;
    printf("%d\n", root->type);
}
