/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:45:40 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/20 16:43:20 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast *create_ast_node(t_cmd *cmd) {
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
    node->cmd = cmd;
    node->left = NULL;
    node->right = NULL;
    return node;
}

const char* cmd_type_to_string(enum s_token_type type) {
    switch (type) {
        case AND: return "AND";
        case OR: return "OR";
        case PIPE: return "PIPE";
        case WORD: return "COMMAND";
        default: return "UNKNOWN";
    }
}

void join_tree(t_ast *left, t_ast *right, t_ast *root) {
    root->left = left;
    root->right = right;
}

void print_ast(t_ast *root, int depth, char prefix) {
    if (root == NULL) {
        return;
    }

    // Imprimer le préfixe pour les branches
    if (depth > 0) {
        printf("%*s", depth * 4, "");
        printf("%c--- ", prefix);
    }

    // Imprimer le nœud courant
    if (root->cmd->cmd[0] && root->cmd->type == WORD) {
        printf("%s: %s\n", cmd_type_to_string(root->cmd->type), root->cmd->cmd[0]);
    } else {
        printf("%s\n", cmd_type_to_string(root->cmd->type));
    }

    // Appel récursif pour les sous-arbres gauche et droit
    print_ast(root->left, depth + 1, '|');
    print_ast(root->right, depth + 1, '`');
}

t_ast *build_ast_recursive(t_cmd *start, t_cmd *end) 
{
    t_cmd *current = end;
    t_cmd *root = NULL;
    t_cmd *left_end = NULL;
    t_cmd *right_start = NULL;

    // Trouver le root => opérateur le plus à droite + opérateur le plus fort
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

    // Si aucun opérateur n'a été trouvé, retourner un noeud AST simple
    if (!root) {
        return create_ast_node(start);
    }

    // Déterminer les points d'arrêt
    left_end = root->prev;
    right_start = root->next;

    // Construire les sous-arbres gauche et droit
    t_ast *gauche = build_ast_recursive(start, left_end);
    t_ast *droit = build_ast_recursive(right_start, end);

    // Créer le noeud racine et joindre les sous-arbres
    t_ast *root_node = create_ast_node(root);
    join_tree(gauche, droit, root_node);
    return root_node;
}
