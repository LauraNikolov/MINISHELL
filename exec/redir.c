/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:43:21 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/06/25 21:17:01 by lauranicolo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redir_in(t_cmd *cmd)
{
    int fd;
    //char *last_redir;
    t_redir *current = cmd->redir;
    t_redir *save = cmd->redir;

    fd = -1;
    if(!cmd->redir)
        return(-1);
    else
    {
        while(current && current->next)
        {
            if(current->type == R_IN)
            { 
                fd = open(current->next->redir, O_RDONLY, O_TRUNC, 0644);
            }
            else if(current->type == R_HEREDOC)
                fd = open(current->next->redir, O_RDONLY, 0644);
            else
            {
                current = current->next;
                continue;
            }
            if(fd == -1)
            {
                perror("minishell");
                return(-1);
            }
            if(!current->next->next)
                break;
            else
                close(fd);
            //last_redir = current->redir;
            current = current->next;
        }
        cmd->redir = save;
    }
    return(fd);
}

int redir_out(t_cmd *cmd)
{
    int fd;
    //char *last_redir;
    t_redir *current = cmd->redir;
    t_redir *save = cmd->redir;

    fd = -1;
    if(!cmd->redir)
        return(-1);
    else
    {
        while(current && current->next)
        {
            if(current->type == R_OUT)
            { 
                fd = open(current->next->redir, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            }
            else if(current->type == R_APPEND)
                fd = open(current->next->redir, O_WRONLY| O_APPEND | O_CREAT, 0644);
            else
            {
                current = current->next;
                continue;
            }
            if(fd == -1)
            {
                perror("minishell");
                return(-1);
            }
            if(!current->next->next)
                break;
            else
                close(fd);
            current = current->next;
        }
    }
     cmd->redir = save;
    return(fd);
}

