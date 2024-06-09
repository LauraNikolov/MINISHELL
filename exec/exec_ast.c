/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:30 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/09 16:06:54 by lauranicolo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


   int ft_execve_single_cmd(t_cmd *cmd, char **envp)
{
    int return_value = 0;
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        if(cmd->std_in != STDIN_FILENO)
        {
            dprintf(2, "Redirection std_in : %d\n", cmd->std_in);
            dup2(cmd->std_in, STDIN_FILENO);
            close(cmd->std_in);
        }
        if(cmd->std_out != STDOUT_FILENO)
        {
            dprintf(2, "Redirection std_out : %d\n", cmd->std_out);
            dup2(cmd->std_out, STDOUT_FILENO);
            close(cmd->std_out);
        }
        execve(cmd->path, cmd->cmd, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &return_value, 0);
    }
    return return_value;
}

int ft_execve_pipe(t_cmd *cmd, char **envp, t_ast *root)
{
    int return_value = 0;
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        if (cmd->std_in != STDIN_FILENO)
        {
            dup2(cmd->std_in, STDIN_FILENO);
            close(cmd->std_in);
        }
        dprintf(2, "avant le dup stdout == %d, et cmd->std_out %d\n", STDOUT_FILENO, cmd->std_out);
        if (cmd->std_out != STDOUT_FILENO)
        {
            dup2(cmd->std_out, STDOUT_FILENO);
            close(cmd->std_out);
            dprintf(2, "STDOUT == %d\n", cmd->std_out);
        }
        // Fermer les descripteurs de pipe inutilisés dans le processus enfant
        close(root->cmd->pipe[0]);
        execve(cmd->path, cmd->cmd, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Fermer les descripteurs inutilisés dans le processus parent
        close(root->cmd->pipe[1]);
        if (root->cmd->prev_fd != -1)
            close(root->cmd->prev_fd);
        root->cmd->prev_fd = root->cmd->pipe[0];
    }
    return return_value;
}

int exec_leaf(t_ast *root, char **envp)
{
    if (root->left->cmd->type == WORD && root->right->cmd->type == WORD)
    {
        t_cmd *cmd1 = root->left->cmd;
        t_cmd *cmd2 = root->right->cmd;
        if (root->cmd->type == PIPE)
        {
            if (pipe(root->cmd->pipe) == -1)
            {
                perror("pipe");
                return (1);
            }
            // cmd1: stdin est standard, stdout est l'entrée du pipe
            cmd1->std_in = STDIN_FILENO;
            cmd1->std_out = root->cmd->pipe[1];
            root->cmd->return_value = ft_execve_pipe(cmd1, envp, root);

            // cmd2: stdin est la sortie du pipe précédent, stdout est l'entrée du pipe
            if (pipe(root->cmd->pipe) == -1)
            {
                perror("pipe");
                return (1);
            }
            cmd2->std_in = root->cmd->prev_fd;
            cmd2->std_out = root->cmd->pipe[1];
            dprintf(2, "cmd2 stdout: %d\n", cmd2->std_out);
            root->cmd->return_value = ft_execve_pipe(cmd2, envp, root);
        }
        if (root->cmd->type == AND)
        {
            root->cmd->return_value = ft_execve_single_cmd(cmd1, envp);
            if (root->cmd->return_value == 0)
                root->cmd->return_value = ft_execve_single_cmd(cmd2, envp);
        }
        if (root->cmd->type == OR)
        {
            root->cmd->return_value = ft_execve_single_cmd(cmd1, envp);
            if (root->cmd->return_value != 0)
                root->cmd->return_value = ft_execve_single_cmd(cmd2, envp);
        }
    }

    return root->cmd->return_value;
}

int exec_ast_recursive(t_ast *root, char **envp)
{
    if (root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        exec_ast_recursive(root->left, envp);
    
    if (root->left->cmd->type == WORD && root->right->cmd->type == WORD)
    {
        dprintf(2, "\n\nje suis la feuille\n");
        print_ast(root, 0, ' ');
        root->cmd->return_value = exec_leaf(root, envp);
    }
    else
    {
        dprintf(2, "\n\nje suis la branche\n");
        print_ast(root, 0, ' ');
         // * si la droite est une branche
        if(root->right->cmd->type == PIPE)
        {
            root->right->cmd->prev_fd = root->left->cmd->prev_fd;
            exec_ast_recursive(root->right, envp);
        }
        else
        {
            pipe(root->cmd->pipe);
            dprintf(2, "fd prev : %d\n", root->left->cmd->prev_fd);
            root->right->cmd->std_in = root->left->cmd->prev_fd;
            root->right->cmd->std_out = STDOUT_FILENO;
            ft_execve_pipe(root->right->cmd, envp, root);
        }
    }
    int i = 4;
    while (i != 0)
    {
        wait(0);
        i--;
    }
    return (root->cmd->return_value);
}


/*
* une fonction qui execute une commande simple : 
* une fonction qui set le pipe
* une fonction qui set le AND
* une fonction qui set le OR
* une fonction qui gere les enfants
* une fonction qui gere le parent
*/

