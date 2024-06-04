/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:40:05 by melmarti          #+#    #+#             */
/*   Updated: 2024/06/04 17:58:47 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	printf ("dir = %s\n", s2);
	printf ("cmd = %s\n", s1);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && i < n
		&& s1[i] && s2[i])
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
/*int main (void)
{
	char *s1 = "";
	char *s2 = "";

	int i = 1;

	printf ("%d\n", ft_strncmp(s1, s2, i));
	printf ("%d", strncmp(s1, s2, i));
}*/