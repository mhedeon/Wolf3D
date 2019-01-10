/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:17:21 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/04 19:17:21 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memalloc(size_t size)
{
	unsigned long	i;
	void			*memory;

	i = 0;
	memory = malloc(size);
	if (!memory)
		return (NULL);
	while (i < size)
	{
		*((char *)(memory + i)) = 0;
		i++;
	}
	return (memory);
}
