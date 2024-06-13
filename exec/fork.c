/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:59:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/13 12:49:31 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_exec_tree(t_ast *root)
{
    int i;
    i = 0;
    
    (void)root;
    printf("CECI EST LE ROOT : \n");
    print_ast(root, 0 ,' ');
    return(i);
}

// void set_exec_struct(t_exec **exec)
// {
//     *exec = (t_exec *)malloc(sizeof(t_exec));
//     if(*exec == NULL)
//     {
//         dprintf(2, "malloc error exec\n");
//         exit(EXIT_FAILURE);
//     }
//    (*exec)->return_value = 0;
//    (*exec)->std_in = STDIN_FILENO;
//    (*exec)->std_out = STDOUT_FILENO;
//    (*exec)->prev = -1;
// }



void ft_exec_multi_cmds(save_struct *t_struct, char **envp)
{
    t_cmd *start; 
    t_cmd *end;
    int return_value = -1;

    start =  t_struct->cmd;
    while(t_struct->cmd->next)
        t_struct->cmd = t_struct->cmd->next;
    end = t_struct->cmd;
    t_struct->cmd = start;
    t_struct->ast = build_ast_recursive(start, end);
    start = t_struct->cmd;
    while(start)
    {
        start->std_in = STDIN_FILENO;
        start->std_out = STDOUT_FILENO;
        start->prev_fd = -1;
        start->return_value = 0;
        start = start->next;
    }
    //set_exec_struct(&exec);
    return_value = exec_ast_recursive(t_struct->ast, envp, t_struct->ast, return_value, t_struct); 
    //set la valeur de retour dans la liste chainee envp (fqire un itoa)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
}
