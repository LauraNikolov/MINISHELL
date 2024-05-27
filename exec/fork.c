/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/27 17:21:03 by lnicolof         ###   ########.fr       */
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

int ft_exec_tree(t_ast *root)
{
    int i;
    i = 0;
    
    (void)root;
    printf("CECI EST LE ROOT : \n");
    print_ast(root, 0 ,' ');
    return(i);
}
int exec_ast_recursive(t_ast *root)
{
    int return_value;
    return_value = -25;

    if(!root)
        return(0);
    if(root->left->cmd->type == PIPE || root->left->cmd->type == AND || root->left->cmd->type == OR)
        exec_ast_recursive(root->left);
    if(root->right->cmd->type == PIPE || root->right->cmd->type == AND || root->right->cmd->type == OR)
        exec_ast_recursive(root->right);
    ft_exec_tree(root);
    return(return_value);                                                                                                                                                                                                                                                                                                                                                                        
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
    exec_ast_recursive(t_struct->ast);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}
