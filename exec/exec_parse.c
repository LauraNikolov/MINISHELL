/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/13 14:58:32 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void ft_build_ast(save_struct *t_struct, char **envp)
// {
    
//     if(cmd_size == 1)
//     {
//         ft_exec_single_cmd(t_struct, envp);
//         return ;
//     }
//     else
//     {
        
//     }
    
//     //je construit l'ast
// }


void ft_exec(save_struct *t_struct, char **envp)
{
    int cmd_size;
    cmd_size = ft_lst_size(t_struct->cmd);
    if(cmd_size == 1)
    {
        ft_exec_single_cmd(t_struct, envp);
        return ;
    }
    // else
    // {
    //     ft_build_ast(t_struct, envp);
    // }
}