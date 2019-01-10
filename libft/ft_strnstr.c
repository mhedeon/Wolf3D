/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 19:48:01 by mhedeon           #+#    #+#             */
/*   Updated: 2018/03/28 19:48:02 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)(haystack));
	j = (unsigned long)*haystack;
	while ((int)i < (int)(len - ft_strlen(needle) + 1) && *(haystack + i))
	{
		j = 0;
		while ((int)j < (int)(ft_strlen(needle)))
		{
			if (*(haystack + i + j) != *(needle + j))
				break ;
			if ((int)j == (int)(ft_strlen(needle) - 1))
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
