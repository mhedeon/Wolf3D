/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:11:17 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 19:11:17 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_mem(char const *s, char c)
{
	int		i;
	int		size;
	char	**new;

	i = 0;
	size = 0;
	if (!s || !ft_strlen(s))
	{
		new = (char **)malloc(sizeof(char *));
		*new = 0;
		return (new);
	}
	while (*(s + i))
	{
		while (*(s + i) == c)
			i++;
		while (*(s + i) != c && *(s + i) != '\0')
			i++;
		size++;
		if (*(s + i) == '\0' && ft_strlen(s) && *(s + i - 1) != c)
			size++;
	}
	new = (char **)malloc(sizeof(char *) * size);
	return (new);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**result;

	i = 0;
	j = 0;
	result = ft_mem(s, c);
	if (!result || !s || !ft_strlen(s))
		return (result);
	while (*(s + i))
	{
		while (*(s + i) == c)
			i++;
		start = i;
		if (*(s + i) == '\0')
			break ;
		while (*(s + i) != c && *(s + i) != '\0')
			i++;
		*(result + j) = ft_memalloc(i - start + 1);
		*(result + j) = ft_strncat(*(result + j), s + start, i - start);
		j++;
	}
	*(result + j) = 0;
	return (result);
}
