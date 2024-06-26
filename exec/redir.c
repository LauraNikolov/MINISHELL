/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauranicoloff <lauranicoloff@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:43:21 by lauranicolo       #+#    #+#             */
/*   Updated: 2024/06/26 18:12:12 by lauranicolo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_limiter(char *s1, char *s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s2[i])
	{
		y = 0;
		while (s2[i] == s1[y] && s1[y] && s2[i])
		{
			i++;
			y++;
			if (y == (int)ft_strlen(s1))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*create_here_doc(char *str, char *limiter)
{
	int		file;
	char	*line;

	file = open(str, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (file == -1)
		perror("open:");
	while (1)
	{
		write(1, "here_doc>  ", 10);
		line = get_next_line(STDOUT_FILENO);
		if (line == NULL)
			printf("malloc error\n");
		if (ft_limiter(limiter, line) == 1)
			break ;
		write(file, line, ft_strlen(line) - 1);
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	close(file);
    return(str);
}

void manage_heredoc(t_cmd *cmd)
{
    int i;
    
    t_cmd *current;
    t_redir *current_redir;
    char *heredocname;

    i = 0;
    current = cmd;
    current_redir = current->redir;
    while(current)
    {
        current_redir = current->redir;
        if(!current->redir)
        {
            current = current->next;
            continue ; 
        }

        else
        {
            while(current_redir && current_redir->type == R_HEREDOC)
            {
                heredocname = ft_strjoin(ft_itoa(i), "heredoctmp");
                if(current_redir->type == R_HEREDOC)
                   current_redir->next->redir = create_here_doc(heredocname, current_redir->next->redir);
                current_redir = current_redir->next->next;
                i++;
            }
        }
        current = current->next;
    }
}


int redir_in(t_cmd *cmd)
{
    dprintf(2, "koukou\n");
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
            {
                fd = open(current->next->redir, O_RDONLY, 0644);
            }
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
        while(current)
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
            current = current->next->next;
        }
    }
     cmd->redir = save;
    return(fd);
}

int check_redir_in(t_redir *redir)
{
    t_redir *current;
    current = redir;
    while(current)
    {
        if(current->type == R_HEREDOC)
            return(0);
        else if(current->type == R_IN)
            return(0);
        if(!current->next->next)
            return(1);
        else
            current = current->next->next;
    }
    return(1);
}
int check_redir_out(t_redir *redir)
{
    t_redir *current;
    current = redir;
    while(current)
    {
        if(current->type == R_OUT)
            return(0);
        else if(current->type == R_APPEND)
            return(0);
        if(!current->next->next)
            return(1);
        else
            current = current->next->next;
    }
    return(1);
}

void apply_redir(t_cmd *cmd)
{
    if(!cmd->redir)
        return;
    dprintf(2, "before in == %d out == %d et cmd == %s\n", cmd->std_in, cmd->std_out, cmd->cmd[0]);
	if(check_redir_in(cmd->redir) != 1)
		cmd->std_in = redir_in(cmd);
	if(check_redir_out(cmd->redir) != 1)
		cmd->std_out = redir_out(cmd);
    dprintf(2, "in == %d out == %d et cmd == %s\n", cmd->std_in, cmd->std_out, cmd->cmd[0]);
}
