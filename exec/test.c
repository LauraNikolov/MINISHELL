
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 #include <sys/types.h>
#include <sys/wait.h>



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
    char *path;
    char **args;
} t_cmd;

typedef struct t_ast {
    t_cmd *cmd;
    struct t_ast *left;
    struct t_ast *right;
} t_ast;

typedef struct s_exec
{
	int pipe[2];
    int std_in;
    int std_out;
    int return_value;
    int prev;
	char **envp;
} t_exec;


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


int ft_execve_pipe(t_cmd *cmd, char **envp, t_exec *exec)
{
    int return_value = 0;
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        close(exec->pipe[0]);
        if(exec->std_in != STDIN_FILENO)
        {
            dup2(exec->std_in, STDIN_FILENO);
            close(exec->std_in);
        }
        if(exec->std_out != STDOUT_FILENO)
        {
            dup2(exec->std_out, STDOUT_FILENO);
            close(exec->std_out);
        }
        return_value = execve(cmd->path, cmd->args, envp);
    }
    else
    {
        close(exec->pipe[1]);
        exec->prev = exec->pipe[0];
    }
    return (return_value);
}

int ft_execve_single_cmds(t_cmd *cmd, char **envp, t_exec *exec)
{
    int return_value = 0;
    pid_t pid;
    int status;
    pid = fork();

    if(pid == -1)
    {
        perror("fork");
        return (1);
    }
    if(pid == 0)
        exec->return_value = execve(cmd->path, cmd->args, envp);
    else
    {
        wait(NULL);
    }
    return (exec->return_value);
    
}


int exec_ast_recursive(t_ast *root, char **envp, t_exec *exec) {
    if (root == NULL) {
        return(0);
    }

    if(root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        exec_ast_recursive(root->left, envp, 0);
    if(root->right->cmd->type == PIPE || root->right->cmd->type == AND || root->right->cmd->type == OR)
        exec_ast_recursive(root->right, envp, 0);

    // Exécuter le nœud courant
   if(root->left->cmd->type == COMMAND && root->right->cmd->type == COMMAND)
   {
        t_cmd *cmd1 = root->left->cmd;
        t_cmd *cmd2 = root->right->cmd;
        int pfd[2];
        pipe(pfd);
        if(root->cmd->type == PIPE)
        {
            exec->std_in = 0;
            exec->std_out = pfd[1];
            ft_execve_pipe(cmd1, envp, exec);
            pipe(pfd);
            exec->std_in = exec->prev;
            exec->std_out = STDOUT_FILENO;
            exec->return_value = ft_execve_pipe(cmd2, envp, exec);
        }

        if(root->cmd->type == AND)
        {
            t_cmd *cmd1 = root->left->cmd;
            t_cmd *cmd2 = root->right->cmd;
            exec->std_in = 0;
            exec->std_out = 1;
            exec->return_value = ft_execve_single_cmds(cmd1, envp, exec);
            if(exec->return_value == 0)
            {
                exec->std_in = 0;
                exec->std_out = 1;
                exec->return_value = ft_execve_single_cmds(cmd2, envp, exec);
            }
            else
            {
                exec->return_value = 1;
                printf("error\n");
            }
        }

    }
    return (exec->return_value);
}

int main(int argc, char **argv, char **envp) 
{
    char* cmd1_args[] = {"echo", "bonjour", NULL};
    char* cmd3_args[] = {"ls", NULL};
    // Création d'exemple de commandes
    t_cmd cmd1 = {COMMAND, NULL, NULL, "echo", "/bin/echo", cmd1_args};
    t_cmd cmd2 = {AND, &cmd1, NULL, NULL, NULL, NULL};
    t_cmd cmd3 = {COMMAND, &cmd2, NULL, "ls", "/bin/ls", cmd3_args};
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
    t_ast *ast = build_ast_recursive(&cmd1, &cmd3);

    // Impression de l'AST
      print_ast(ast, 0, ' ');

    t_exec *exec;
    exec = (t_exec *)malloc(sizeof(t_exec));
    exec->std_in = STDIN_FILENO;
    exec->std_out = STDOUT_FILENO;
    exec->prev = -1;
    exec_ast_recursive(ast, envp, exec);

    return 0;
}