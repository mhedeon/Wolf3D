/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:34:30 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/04 19:34:30 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnew(size_t size)
{
	unsigned long	i;
	char			*new_string;

	i = 0;
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_string)
		return (NULL);
	while (i < size + 1)
	{
		*(new_string + i) = '\0';
		i++;
	}
	return (new_string);
}
