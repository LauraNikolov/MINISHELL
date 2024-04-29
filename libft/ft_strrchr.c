/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:02:11 by melmarti          #+#    #+#             */
/*   Updated: 2023/11/17 17:18:12 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	j;

	j = 0;
	while (s[j])
		j++;
	while (j >= 0)
	{
		if (s[j] == (unsigned char)c)
			return ((char *)(s + j));
		j--;
	}
	if (!j && (!s[j]))
		return ((char *)(s + j));
	else
		return (NULL);
}
