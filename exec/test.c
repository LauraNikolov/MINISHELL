
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum {
    AND,
    OR,
    PIPE,
    COMMAND
} t_cmd_type;

typedef struct t_cmd {
    t_cmd_type type;
    struct t_cmd *prev;
    struct t_cmd *next;
    char *cmd_str;
} t_cmd;

typedef struct t_ast {
    t_cmd *cmd;
    struct t_ast *left;
    struct t_ast *right;
} t_ast;


const char* cmd_type_to_string(t_cmd_type type) {
    switch (type) {
        case AND: return "AND";
        case OR: return "OR";
        case PIPE: return "PIPE";
        case COMMAND: return "COMMAND";
        default: return "UNKNOWN";
    }
}

void join_tree(t_ast *left, t_ast *right, t_ast *root) {
    root->left = left;
    root->right = right;
}

t_ast *create_ast_node(t_cmd *cmd) {
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
    node->cmd = cmd;
    node->left = NULL;
    node->right = NULL;
    return node;
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
    if (root->cmd->cmd_str) {
        printf("%s: %s\n", cmd_type_to_string(root->cmd->type), root->cmd->cmd_str);
    } else {
        printf("%s\n", cmd_type_to_string(root->cmd->type));
    }

    // Appel récursif pour les sous-arbres gauche et droit
    print_ast(root->left, depth + 1, '|');
    print_ast(root->right, depth + 1, '`');
}




t_ast *build_ast_recursive(t_cmd *start, t_cmd *end) {
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


int main() {
    // Création d'exemple de commandes
    t_cmd cmd1 = {COMMAND, NULL, NULL, "ls -la"};
    t_cmd cmd2 = {PIPE, &cmd1, NULL, NULL};
    t_cmd cmd3 = {COMMAND, &cmd2, NULL, "cat"};
    t_cmd cmd4 = {AND, &cmd3, NULL, NULL};
    t_cmd cmd5 = {COMMAND, &cmd4, NULL, "ls"};
    t_cmd cmd6 = {PIPE, &cmd5, NULL, NULL};
    t_cmd cmd7 = {COMMAND, &cmd6, NULL, "cat -e"};
    t_cmd cmd8 = {AND, &cmd7, NULL, NULL};
    t_cmd cmd9 = {COMMAND, &cmd8, NULL, "echo bonjour"};
    
    cmd1.next = &cmd2;
    cmd2.next = &cmd3;
    cmd3.next = &cmd4;
    cmd4.next = &cmd5;
    cmd5.next = &cmd6;
    cmd6.next = &cmd7;
    cmd7.next = &cmd8;
    cmd8.next = &cmd9;

    // Construction de l'AST
    t_ast *ast = build_ast_recursive(&cmd1, &cmd9);

    // Impression de l'AST
      print_ast(ast, 0, ' ');

    return 0;
}