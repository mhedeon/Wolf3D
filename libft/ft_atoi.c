/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:45:57 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/04 16:45:58 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *nptr)
{
	long long int	number;
	int				negative;

	number = 0;
	negative = FALSE;
	while (*nptr == '\n' || *nptr == '\t' || *nptr == '\v' ||
			*nptr == '\r' || *nptr == '\f' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		negative = TRUE;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		number *= (long long int)10;
		number += (long long int)(*nptr - '0');
		nptr++;
		if (number < 0)
			return (negative == FALSE ? -1 : 0);
	}
	if (negative)
		number *= -1;
	return ((int)number);
}
