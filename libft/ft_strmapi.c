/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:46:05 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 16:46:05 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	new = NULL;
	if (s)
	{
		i = 0;
		new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!new)
			return (NULL);
		ft_bzero(new, sizeof(new));
		while (i < ft_strlen(s))
		{
			*(new + i) = (*f)(i, *(s + i));
			i++;
		}
		*(new + i) = '\0';
	}
	return (new);
}
