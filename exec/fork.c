/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/24 18:44:59 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exec_single_cmd(save_struct *t_struct, char **envp)
{
    int return_value = 0;
    pid_t pid;
    pid = fork();
    if(pid == 0)
        return_value = execve(t_struct->cmd->path, t_struct->cmd->cmd, envp);
    else if(pid != -1)
        wait(NULL);
    if(return_value < 0)
        printf("%s\n", strerror(errno));
    return(0); 
}

// ! dernier entre, dernier sorti
// ? d'abord la gauche ou les deux en meme temps?
void exec_ast(t_ast *root, int pfd[2])
{
    enum t_token_type ope;
    t_ast *current_tree_left;
    t_ast *current_tree_right;
    int pfd[2];
    
    if(!root->left)
        return ;

    if(!root->right)
        return ;
        
    current_tree_left = root->left;
    current_tree_right = root->right;
    
    if(!current_tree_left->left)
        exec_ast(current_tree_left);
    if(!current_tree_right->right)
        exec_ast(current_tree_right);
    // ? est ce qie y'a un pipe?

    // ? est ce que je dois analyser la valeur de retour de gauche avant d'exec le droit                                                                                                                                                                                                                                                                                                                                                                                   
}

void ft_exec_multi_cmds(save_struct *t_struct, char **envp)
{
    (void)envp;
    t_cmd *start; 
    t_cmd *end;

    start = t_struct->cmd;
    while(t_struct->cmd->next)
        t_struct->cmd = t_struct->cmd->next;
    end = t_struct->cmd;
    t_struct->cmd = start;
    t_struct->ast = build_ast_recursive(start, end);
    print_ast(t_struct->ast, 0, ' ');
    exec_ast(t_struct);
}
