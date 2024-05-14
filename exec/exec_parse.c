/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/14 19:12:57 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exec(save_struct *t_struct, char **envp)
{
    t_cmd *last;
    int cmd_size;
    
    cmd_size = ft_lst_size(t_struct->cmd);
    ft_get_path(t_struct->cmd);
    if(cmd_size == 1)
    {
        ft_exec_single_cmd(t_struct, envp);
        return ;
    }
    else
    {
        
    }
}