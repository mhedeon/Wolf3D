/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 20:49:37 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 20:49:37 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	long	nbr;
	char	tmp[11];

	i = 0;
	nbr = n;
	if (nbr == 0)
		ft_putchar_fd('0', fd);
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	while (nbr > 0)
	{
		tmp[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	while (--i >= 0)
		ft_putchar_fd(tmp[i], fd);
}
