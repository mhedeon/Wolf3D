/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:56:35 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 17:56:36 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*new;

	if (!s)
		return (NULL);
	start = 0;
	while (*(s + start) == '\n' || *(s + start) == '\t' || *(s + start) == ' ')
		start++;
	if (start == ft_strlen(s))
		return (ft_memalloc(1));
	end = ft_strlen(s) - 1;
	while (*(s + end) == '\n' || *(s + end) == '\t' || *(s + end) == ' ')
		end--;
	new = (char *)malloc(sizeof(char) * (end - start + 1 + 1));
	if (!new)
		return (start < end ? NULL : ft_memalloc(1));
	ft_strncpy(new, s + start, end - start + 1);
	*(new + end - start + 1) = '\0';
	return (new);
}
