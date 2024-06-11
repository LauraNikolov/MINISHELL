/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:11:57 by lnicolof          #+#    #+#             */
/*   Updated: 2024/06/11 17:41:09 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(char *str, int len)
{
	char	*array;
	int		count;

	if (!str || !len)
		return (NULL);
	count = -1;
	array = (char *)malloc((len + 1) * sizeof(char));
	while (++count < len)
		array[count] = str[count];
	array[count] = '\0';
	return (array);
}

char	*ft_strjoin_gnl(char const *s1, char *s2)
{
	char	*cpy;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup_gnl(s2, ft_strlen(s2)));
	cpy = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		cpy[i++] = s2[j++];
	}
	cpy[i] = '\0';
	if (s1)
		free((char *)s1);
	return (cpy);
}
