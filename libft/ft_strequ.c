/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:07:23 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/05 17:07:23 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (*(s1 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (FALSE);
		i++;
	}
	if (*(s1 + i) != *(s2 + i))
		return (FALSE);
	return (TRUE);
}
