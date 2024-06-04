/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:30 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/04 13:26:38 by lauranicolo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve_pipe(t_cmd *cmd, char **envp, t_exec *exec)
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
        // Je ferme la sortie du pipe
        if (exec->std_in != STDIN_FILENO)
        {
            dup2(exec->std_in, STDIN_FILENO);
            close(exec->std_in);
            close(exec->pipe[0]);
        }
        if (exec->std_out != STDOUT_FILENO)
        {
            dup2(exec->std_out, STDOUT_FILENO);
            close(exec->std_out);
        }
        execve(cmd->path, cmd->cmd, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(exec->pipe[1]);
        if (exec->prev != -1)
            close(exec->prev);
        exec->prev = exec->pipe[0];
    }
    return return_value;
}

int exec_leaf(t_ast *root, char **envp, t_exec *exec)
{
    if (root->left->cmd->type == WORD && root->right->cmd->type == WORD)
    {
        t_cmd *cmd1 = root->left->cmd;
        t_cmd *cmd2 = root->right->cmd;
        if (root->cmd->type == PIPE)
        {
            if (pipe(exec->pipe) == -1)
            {
                perror("pipe");
                return (1);
            }
            // Mon stdin est standard
            exec->std_in = STDIN_FILENO;
            // Mon stdout est l'entrée du pipe
            exec->std_out = exec->pipe[1];
            ft_execve_pipe(cmd1, envp, exec);

            // Préparer pour la commande suivante
            exec->std_in = exec->prev;
            exec->std_out = STDOUT_FILENO;
            exec->return_value = ft_execve_pipe(cmd2, envp, exec);
        }
    }
    return exec->return_value;
}

int exec_ast_recursive(t_ast *root, char **envp, t_exec *exec)
{
    if (root == NULL) {
        return(0);
    }

    if(root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        exec_ast_recursive(root->left, envp, exec);
    if(root->right->cmd->type == PIPE || root->right->cmd->type == AND || root->right->cmd->type == OR)
        exec_ast_recursive(root->right, envp, exec);
    
    if(root->left->cmd->type == WORD && root->right->cmd->type == WORD)
    {
        exec->return_value = exec_leaf(root, envp, exec);
        int i = 0;
        while(i != 2)
        {
            wait(NULL);
            i++;
        }
    }
    return (exec->return_value);
}

/*
* une fonction qui execute une commande simple : 
* une fonction qui set le pipe
* une fonction qui set le AND
* une fonction qui set le OR
* une fonction qui gere les enfants
* une fonction qui gere le parent
*/

