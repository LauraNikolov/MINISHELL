/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/13 14:45:59 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_build_ast(save_struct *t_struct, char **envp)
{
    //je check si y'a qu'une seule commande
    int cmd_size;

    //je check si y'a des operateurs
    ft_get_path(t_struct->cmd);
    cmd_size = ft_lst_size(t_struct->cmd);
    if(cmd_size == 1)
    {
        ft_exec_single_cmd(t_struct, envp);
    }
    //je construit l'ast
}


void ft_exec(save_struct *t_struct, char **envp)
{
    ft_build_ast(t_struct, envp);
    //exec_ast(t_struct);
}