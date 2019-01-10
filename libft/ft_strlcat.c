/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:59:04 by mhedeon           #+#    #+#             */
/*   Updated: 2018/03/25 19:59:04 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	return_v;

	i = 0;
	if (dstsize < ft_strlen(dst))
		return_v = ft_strlen(src) + dstsize;
	else
		return_v = ft_strlen(dst) + ft_strlen(src);
	if (dstsize <= ft_strlen(dst))
		return (return_v);
	while ((int)i < (int)(dstsize - 1) && *(dst + i))
		i++;
	while ((int)i < (int)(dstsize - 1) && *src)
	{
		*(dst + i) = *src;
		src++;
		i++;
	}
	*(dst + i) = '\0';
	return (return_v);
}
