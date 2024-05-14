/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:45:40 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/14 19:11:38 by lnicolof         ###   ########.fr       */
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

t_cmd *find_root_nods(t_cmd *start, t_cmd *end)
{
    t_cmd *current;

    current = end;
    while(current != start)
    {
        if(current->type == AND || current->type == OR)
            return(current);
        current = current->prev;
    }
    current = end;
    while(current != start)
    {
        if(current->type == PIPE)
            return(current);
        current = current->prev;
    }
    return(current = NULL);
}


t_ast *build_ast_recursive(t_cmd *start, t_cmd *end)
{
    t_cmd *current = end;
    t_cmd *root = NULL;
    t_cmd *left_end = NULL;
    t_cmd *right_start = NULL;

    // * Trouver le dernier opérateur le plus à droite
     while (current != start) {
        if (current->type == AND || current->type == OR) {
            root = current;
            break;
        }
        current = current->prev;
    }

    if (!root) {
        // Si aucun opérateur && ou || n'a été trouvé, trouvez le dernier pipe
        current = end;
        while (current != start) {
            if (current->type == PIPE) {
                root = current;
                break;
            }
            current = current->prev;
        }
    }
    // * definir le point d'arret
    if(!root)
         return build_ast_recursive(start, end);
    // * determiner les points d'arrets
    left_end = root->prev;
    right_start = root->next;
    // * constuire les arbres
    t_ast *gauche = build_ast_recursive(start, left_end);
    t_ast *droit = build_ast_recursive(right_start, end);
    
    // * join les arbres
    t_ast *root_node = create_ast_node(root);
    root_node->left = gauche;
    root_node->right = droit;
    return(root_node);
}

/* 

* trouver le root => le root = operateur le plus a droite + operateur le plus fort
ex : ls -la | cat && ls | cat -e
root = &&

* separer la liste chainee en deux 
gauche : ls -la | cat
droite : ls | cat -e

* si il n'y a pas de && || join tous les sous arbres entre eux
        |                     |

ls -la       cat        ls         cat -e

* si il y a un && et un ||, recommencer l'operation jusqu'a arriver a la condition du haut
*/
