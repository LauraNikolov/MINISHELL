/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:39:58 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/11 17:40:43 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char **stash, int *readed)
{
	char	*tmp;
	char	*cpy;
	int		i;

	if (!*stash && *readed == 0)
		return (NULL);
	tmp = *stash;
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	cpy = ft_strdup_gnl(tmp, i);
	*stash = ft_strdup_gnl(tmp + i, ft_strlen(tmp + i));
	if (!tmp[i])
	{
		free(*stash);
		*stash = NULL;
	}
	if (tmp)
		free(tmp);
	tmp = NULL;
	return (cpy);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			readed;

	readed = 1;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (readed > 0)
	{
		readed = read(fd, line, BUFFER_SIZE);
		line[readed] = '\0';
		stash = ft_strjoin_gnl(stash, line);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (ft_extract_line(&stash, &readed));
}

/* #include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **ag)
{
	int		fd;
	char	*line;

	line = malloc(sizeof(char));
	(void)ac;
	(void)ag;
	fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		printf("%s", line);
	}
	close(fd);
}  */
