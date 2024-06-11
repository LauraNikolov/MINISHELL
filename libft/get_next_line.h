/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:38:18 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/11 17:37:50 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

char	*ft_extract_line(char **stash, int *readed);
char	*ft_strdup_gnl(char *str, int len);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char const *s1, char *s2);
char	*ft_strchr(const char *s, int c);

#endif