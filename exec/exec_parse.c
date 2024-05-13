/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:56:13 by lnicolof          #+#    #+#             */
/*   Updated: 2024/05/13 13:09:45 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_build_ast(save_struct *t_struct)
{
    //je check si y'a qu'une seule commande
    int cmd_size;

    //je check si y'a des operateurs
    cmd_size = ft_lst_size(t_struct->cmd);
    if(cmd_size == 1)
    {
        //recuperer le path;
        //ft_get_path // ! todo;
        ft_exec_single_cmd(t_struct);
    }
    //je construit l'ast
}


void ft_exec(save_struct *t_struct)
{
    build_ast(t_struct);
    exec_ast(t_struct);
}