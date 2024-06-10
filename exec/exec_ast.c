/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:30 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/10 13:50:35 by lnicolof         ###   ########.fr       */
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
            dup2(cmd->std_in, STDIN_FILENO);
            close(cmd->std_in);
        }
        if(cmd->std_out != STDOUT_FILENO)
        {
            dup2(cmd->std_out, STDOUT_FILENO);
            close(cmd->std_out);
        }
        return_value = execve(cmd->path, cmd->cmd, envp);
        if(return_value != 0)
        {
            perror("execve : \n");
            dprintf(2, "cmd->path = %s\n", cmd->path);
        } 
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
        if (cmd->std_out != STDOUT_FILENO)
        {
            dup2(cmd->std_out, STDOUT_FILENO);
            close(cmd->std_out);
            dprintf(2, "STDOUT == %d\n", cmd->std_out);
        }
        // Fermer les descripteurs de pipe inutilisés dans le processus enfant
        close(root->cmd->pipe[0]);
        return_value = execve(cmd->path, cmd->cmd, envp);
        if(return_value != 0)
        {
            perror("execve : \n");
            dprintf(2, "cmd->path = %s\n", cmd->path);
        }
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

int exec_leaf(t_ast *root, char **envp, t_ast *save_root, int return_value)
{
    if(root->cmd->type == WORD)
    {
        return (0);
    }
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
            if(root->cmd->prev_fd == -1)
                cmd1->std_in = STDIN_FILENO;
            else
                cmd1->std_in = root->cmd->prev_fd;
            cmd1->std_out = root->cmd->pipe[1];
            return_value = ft_execve_pipe(cmd1, envp, root);

            // cmd2: stdin est la sortie du pipe précédent, stdout est l'entrée du pipe
            if (pipe(root->cmd->pipe) == -1)
            {
                perror("pipe");
                return (1);
            }
            cmd2->std_in = root->cmd->prev_fd;
            if(root != save_root)
                cmd2->std_out = root->cmd->pipe[1];
            else
                 cmd2->std_out = STDOUT_FILENO;
            if(root->cmd->prev_fd != -1)
            {
                close(root->cmd->prev_fd);
                cmd2->std_out = STDOUT_FILENO;
            }
            dprintf(2, "cmd2 stdout: %d\n", cmd2->std_out);
            return_value = ft_execve_pipe(cmd2, envp, root);
        }
        if (root->cmd->type == AND)
        {
            return_value = ft_execve_single_cmd(cmd1, envp);
            if (return_value == 0)
                return_value = ft_execve_single_cmd(cmd2, envp);
        }
        if (root->cmd->type == OR)
        {
            return_value = ft_execve_single_cmd(cmd1, envp);
            if (return_value != 0)
                return_value = ft_execve_single_cmd(cmd2, envp);
        }
    }

    return (return_value);
}

int exec_ast_recursive(t_ast *root, char **envp, t_ast *save_root, int return_value)
{
    if (root == NULL)
        return (0);
    if (root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        return_value = exec_ast_recursive(root->left, envp, save_root, return_value);
 
    // * feuille : gauche et droite sont des mots
    if (root->left->cmd->type == WORD && root->right->cmd->type == WORD)
    {
        dprintf(2, "\n\nje suis la feuille droite\n");
        print_ast(root, 0, ' ');
        return_value = exec_leaf(root, envp, save_root, return_value);
    }
    else
    {
        dprintf(2, "\n\nje suis la branche droite\n");
        print_ast(root, 0, ' ');
         // * si la droite est une branche
        if(root->right->cmd->type == PIPE || root->right->cmd->type == AND || root->right->cmd->type == OR)
        {
            if(root->cmd->type == AND)
            {
                // * afficher le pipe
                char buffer[1024];
                ssize_t bytes_read;
                while ((bytes_read = read(root->left->cmd->prev_fd, buffer, sizeof(buffer))) > 0)
                    write(STDOUT_FILENO, buffer, bytes_read);
                close(root->cmd->prev_fd);
                if(return_value == 0)
                    return_value = exec_ast_recursive(root->right, envp, save_root, return_value);
                else
                    return(return_value);
            }
            else
            {
                root->right->cmd->prev_fd = root->left->cmd->prev_fd;  
                return_value = exec_ast_recursive(root->right, envp, save_root, return_value);
            }
        }
        {
            if(root->cmd->type == PIPE)
            {
                pipe(root->cmd->pipe);
                root->right->cmd->std_in = root->left->cmd->prev_fd;
                if(save_root != root)
                    root->right->cmd->std_out = root->cmd->pipe[1];
                else
                {
                    root->right->cmd->std_out = STDOUT_FILENO;
                }
                return_value = ft_execve_pipe(root->right->cmd, envp, root);
            }
            if(root->cmd->type == AND)
            {
               // dprintf(2, "je suis le AND\n");
                char buffer[1024];
                ssize_t bytes_read;
                while ((bytes_read = read(root->left->cmd->prev_fd, buffer, sizeof(buffer))) > 0)
                    write(STDOUT_FILENO, buffer, bytes_read);
                close(root->cmd->prev_fd);
                //dprintf(2, "return_value = %d\n", return_value);
                if(return_value == 0)
                    return_value = ft_execve_single_cmd(root->right->cmd, envp);
                else
                    return(-1);
            }
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

