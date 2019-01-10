/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:35:59 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 19:36:00 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	int		i;
	long	nbr;
	char	tmp[11];

	i = 0;
	nbr = n;
	if (nbr == 0)
		ft_putchar('0');
	else if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	while (nbr > 0)
	{
		tmp[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	while (--i >= 0)
		ft_putchar(tmp[i]);
}
