/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:34:41 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 17:34:41 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*join;

	if (!s1 && !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char) * ((s1 ? ft_strlen(s1) : 0) +
			(s2 ? ft_strlen(s2) : 0) + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1 && i < (s1 ? ft_strlen(s1) : 0))
	{
		*(join + i) = *(s1 + i);
		i++;
	}
	i = 0;
	while (s2 && i < (s2 ? ft_strlen(s2) : 0))
	{
		*(join + i + (s1 ? ft_strlen(s1) : 0)) = *(s2 + i);
		i++;
	}
	*(join + i + (s1 ? ft_strlen(s1) : 0)) = '\0';
	return (join);
}
