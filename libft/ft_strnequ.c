/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:12:59 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 17:12:59 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (*(s1 + i) && i < n)
	{
		if (*(s1 + i) != *(s2 + i))
			return (FALSE);
		i++;
	}
	if (*(s1 + i) != *(s2 + i) && i < n)
		return (FALSE);
	return (TRUE);
}
