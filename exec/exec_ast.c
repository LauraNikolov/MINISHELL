/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:30 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/04 18:19:41 by lnicolof         ###   ########.fr       */
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
        // Je ferme la sortie du pipe
        if (cmd->std_in != STDIN_FILENO)
        {
            dup2(cmd->std_in, STDIN_FILENO);
            close(cmd->std_in);
            close(root->cmd->pipe[0]);
        }
        if (cmd->std_out != STDOUT_FILENO)
        {
            dup2(cmd->std_out, STDOUT_FILENO);
            close(cmd->std_out);
        }
        execve(cmd->path, cmd->cmd, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
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
            // Mon stdin est standard
            cmd1->std_in = STDIN_FILENO;
            // Mon stdout est l'entrée du pipe
            cmd1->std_out = root->cmd->pipe[1];
            root->cmd->return_value = ft_execve_pipe(cmd1, envp, root);

            // Préparer pour la commande suivante
            cmd2->std_in = root->cmd->prev_fd;
            cmd2->std_out = root->cmd->pipe[1];
            root->cmd->return_value = ft_execve_pipe(cmd2, envp, root);
        }
        if(root->cmd->type == AND)
        {
            root->cmd->return_value = ft_execve_single_cmd(cmd1, envp);
            if(root->cmd->return_value == 0)
                root->cmd->return_value = ft_execve_single_cmd(cmd2, envp);
        }
        if(root->cmd->type == OR)
        {
            root->cmd->return_value = ft_execve_single_cmd(cmd1, envp);
            if(root->cmd->return_value != 0)
                root->cmd->return_value = ft_execve_single_cmd(cmd2, envp);
        }
    }

    return root->cmd->return_value;
}

int exec_branch(t_ast *root, char **envp)
{
    if(root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
    {
        if(root->left->cmd->type == PIPE)
        {
            if(pipe(root->cmd->pipe) == -1)
            {
                perror("pipe");
                return (1);
            }
            dprintf(2, "prev fd == %d\n", root->left->cmd->prev_fd);
            root->cmd->std_in = root->left->cmd->prev_fd;
            root->cmd->std_out = root->left->cmd->pipe[1];
            root->cmd->return_value = ft_execve_pipe(root->left->cmd, envp, root); // TODO : 
        }
    }
    return(root->cmd->return_value);
}

int exec_ast_recursive(t_ast *root, char **envp)
{
    if (root == NULL) {
        return(0);
    }

    if(root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        exec_ast_recursive(root->left, envp);
    if(root->right->cmd->type == PIPE || root->right->cmd->type == AND || root->right->cmd->type == OR)
        exec_ast_recursive(root->right, envp);
    
    if(root->left->cmd->type == WORD && root->right->cmd->type == WORD)
    {
        root->cmd->return_value = exec_leaf(root, envp);
    }

    else
    {
        root->cmd->return_value = exec_branch(root, envp);
    }
    int i = 0;
    while(i != 2)
    {
        wait(NULL);
        i++;
    }
    // else
    // {
    //     root->cmd->return_value = exec_branch(root, envp, exec);
    // }
    
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

