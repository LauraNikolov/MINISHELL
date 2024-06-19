/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:30 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/19 19:48:33 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_execve_single_cmd(t_cmd *cmd, char **envp, save_struct *t_struct)
{
	(void)t_struct;
    int return_value = 0;
    pid_t pid;
	if((return_value = ft_dispatch_builtin(cmd->cmd, t_struct)) != -1)
		return(return_value);
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
        if(execve(cmd->path, cmd->cmd, envp) == -1)
			ft_parse_error(cmd);
    }
    else
    {
        waitpid(pid, &return_value, 0);
    }
    return return_value;
}

int ft_execve_pipe(t_cmd *cmd, char **envp, t_ast *root, save_struct *t_struct)
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
        }
        // Fermer les descripteurs de pipe inutilisés dans le processus enfant
        close(root->cmd->pipe[0]);
		// ! check builting
		if((return_value = ft_dispatch_builtin(cmd->cmd, t_struct)) != -1)
			exit(return_value);
		else
		{
			if(execve(cmd->path, cmd->cmd, envp) == -1)
				ft_parse_error(cmd);
		}
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

int exec_leaf(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
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
            return_value = ft_execve_pipe(cmd1, envp, root, t_struct);
            // cmd2: stdin est la sortie du pipe précédent, stdout est l'entrée du pipe
            if (pipe(root->cmd->pipe) == -1)
            {
                perror("pipe");
                return (1);
            }
            cmd2->std_in = root->cmd->prev_fd;
            //if(root != save_root)
                //cmd2->std_out = root->cmd->pipe[1];
            if(root != save_root->right)
                    root->right->cmd->std_out = root->cmd->pipe[1];
            if(root == save_root)
                cmd2->std_out = STDOUT_FILENO;
            return_value = ft_execve_pipe(cmd2, envp, root, t_struct);
        }
        if (root->cmd->type == AND)
        {
            return_value = ft_execve_single_cmd(cmd1, envp, t_struct);
            if (return_value == 0)
                return_value = ft_execve_single_cmd(cmd2, envp, t_struct);
        }
        if (root->cmd->type == OR)
        {
            return_value = ft_execve_single_cmd(cmd1, envp, t_struct);
            if (return_value != 0)
                return_value = ft_execve_single_cmd(cmd2, envp, t_struct);
        }
    }

    return (return_value);
}
void read_pipe(int fd)
{
    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
        write(STDOUT_FILENO, buffer, bytes_read);
    close(fd);
}
int	ft_pipe_recursive(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	if (root->right->cmd->type == PIPE
		|| root->right->cmd->type == AND
		|| root->right->cmd->type == OR)
	{
		root->right->cmd->prev_fd = root->left->cmd->prev_fd;
		return_value = exec_ast_recursive(root->right, envp, save_root, return_value, t_struct);
	}
	else
	{
		pipe(root->cmd->pipe);
		root->right->cmd->std_in = root->left->cmd->prev_fd;
		if (root != save_root->right)
			root->right->cmd->std_out = root->cmd->pipe[1];
		if (root == save_root)
			root->right->cmd->std_out = STDOUT_FILENO;
		return_value = ft_execve_pipe(root->right->cmd, envp, root, t_struct);
	}
	return (return_value);
}

int	ft_pipe(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	return (ft_pipe_recursive(root, envp, save_root, return_value, t_struct));
}

int	ft_and_recursive(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	if (root->right->cmd->type == PIPE
		|| root->right->cmd->type == AND
		|| root->right->cmd->type == OR)
	{
		read_pipe(root->left->cmd->prev_fd);
		if (return_value == 0)
			return_value = exec_ast_recursive(root->right, envp, save_root, return_value, t_struct);
		else
			return (return_value);
	}
	else
	{
		read_pipe(root->left->cmd->prev_fd);
		if (return_value == 0)
			return_value = ft_execve_single_cmd(root->right->cmd, envp, t_struct);
		else
			return (return_value);
	}
	return (return_value);
}

int	ft_and(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	return (ft_and_recursive(root, envp, save_root, return_value, t_struct));
}

int	ft_or_recursive(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	if (root->right->cmd->type == PIPE
		|| root->right->cmd->type == AND
		|| root->right->cmd->type == OR)
	{
		read_pipe(root->left->cmd->prev_fd);
		if (return_value != 0)
			return_value = exec_ast_recursive(root->right, envp, save_root, return_value, t_struct);
		else
			return (return_value);
	}
	else
	{
		read_pipe(root->left->cmd->prev_fd);
		if (return_value != 0)
			return_value = ft_execve_single_cmd(root->right->cmd, envp, t_struct);
		else
			return (return_value);
	}
	return (return_value);
}

int	ft_or(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	return (ft_or_recursive(root, envp, save_root, return_value, t_struct));
}

void	ft_handle_ast_recursive(t_ast *root, char **envp, t_ast *save_root, int *return_value, save_struct *t_struct)
{
	if (root->cmd->type == AND)
	{
		//read_pipe(root->left->cmd->prev_fd);
		if (*return_value == 0)
			*return_value = exec_ast_recursive(root->right, envp, save_root, *return_value , t_struct);
		else
			return;
	}
	else if (root->cmd->type == OR)
	{
		//read_pipe(root->left->cmd->prev_fd);
		if (*return_value != 0)
			*return_value = exec_ast_recursive(root->right, envp, save_root, *return_value, t_struct);
		else
			return;
	}
	else
	{
		root->right->cmd->prev_fd = root->left->cmd->prev_fd;
		*return_value = exec_ast_recursive(root->right, envp, save_root, *return_value, t_struct);
	}
}

void	ft_handle_exec(t_ast *root, char **envp, t_ast *save_root, int *return_value, save_struct *t_struct)
{
	if (root->cmd->type == PIPE)
	{
		pipe(root->cmd->pipe);
		root->right->cmd->std_in = root->left->cmd->prev_fd;
		if (root != save_root->right)
			root->right->cmd->std_out = root->cmd->pipe[1];
		if (root == save_root || root->parent->cmd->type == OR || root->parent->cmd->type == AND)
			root->right->cmd->std_out = STDOUT_FILENO;
		*return_value = ft_execve_pipe(root->right->cmd, envp, root, t_struct);
	}
	else if (root->cmd->type == AND)
	{
		if (*return_value == 0)
			*return_value = ft_execve_single_cmd(root->right->cmd, envp, t_struct);
		else
			*return_value = -1;
	}
	else if (root->cmd->type == OR)
	{
		if (*return_value != 0)
			*return_value = ft_execve_single_cmd(root->right->cmd, envp, t_struct);
		else
			*return_value = -1;
	}
}

int	exec_ast_recursive(t_ast *root, char **envp, t_ast *save_root, int return_value, save_struct *t_struct)
{
	int	i;
	print_ast(root, 0, ' ');
	if(root->parent)
		dprintf(2, "parent == %s\n", cmd_type_to_string(root->parent->cmd->type));
	if (root == NULL)
		return (0);
	if (root->left->cmd->type == PIPE
		|| root->left->cmd->type == AND
		|| root->left->cmd->type == OR)
		return_value = exec_ast_recursive(root->left, envp, save_root, return_value, t_struct);
	if (root->left->cmd->type == WORD && root->right->cmd->type == WORD)
		return_value = exec_leaf(root, envp, save_root, return_value, t_struct);
	else
	{
		if (root->right->cmd->type == PIPE
			|| root->right->cmd->type == AND
			|| root->right->cmd->type == OR)
			ft_handle_ast_recursive(root, envp, save_root, &return_value, t_struct);
		else
			ft_handle_exec(root, envp, save_root, &return_value, t_struct);
	}
	i = 4;
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

