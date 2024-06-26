/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:15:59 by melmarti          #+#    #+#             */
/*   Updated: 2024/06/27 15:01:25 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *a, char *b)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (a[i])
		i++;
	while (b[j])
	{
		a[i] = b[j];
		i++;
		j++;
	}
	a[i] = '\0';
	return (a);
}
