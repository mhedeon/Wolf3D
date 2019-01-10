/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:48:46 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/17 18:48:47 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr)
	{
		if (!(new = ft_memalloc(size)))
			return (NULL);
		return (new);
	}
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!(new = ft_memalloc(size)))
		return (NULL);
	ft_strcpy(new, ptr);
	free(ptr);
	return (new);
}
