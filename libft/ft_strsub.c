/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:19:33 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 17:19:34 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = start;
	sub = NULL;
	if (s)
	{
		sub = (char *)malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		ft_bzero(sub, len + 1);
		while (i - start < len && *(s + i))
		{
			*(sub + i - start) = *(s + i);
			i++;
		}
		*(sub + i) = '\0';
	}
	return (sub);
}
