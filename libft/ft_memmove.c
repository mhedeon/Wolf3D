/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:17:46 by mhedeon           #+#    #+#             */
/*   Updated: 2018/03/25 17:17:46 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			*((char *)(dst + i - 1)) = *((char *)(src + i - 1));
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*((char *)(dst + i)) = *((char *)(src + i));
			i++;
		}
	}
	return (dst);
}
