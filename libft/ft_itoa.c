/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:12:50 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 19:12:50 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_mem(int nbr)
{
	size_t		i;

	i = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			i;
	char		*result;

	i = n < 0 ? ft_mem(n) : ft_mem(n) - 1;
	if (n == 0)
	{
		result = ft_memalloc(2);
		*(result + 0) = '0';
		return (result);
	}
	result = (char *)malloc(sizeof(char) * (ft_mem(n) + (n < 0 ? 2 : 1)));
	if (!result)
		return (NULL);
	ft_bzero(result, sizeof(result));
	if (n < 0)
		*(result + 0) = '-';
	*(result + i + 1) = '\0';
	while (n != 0)
	{
		*(result + i) = ft_abs(n % 10) + '0';
		n /= 10;
		i--;
	}
	return (result);
}
