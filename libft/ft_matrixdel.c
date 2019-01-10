/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:06:41 by mhedeon           #+#    #+#             */
/*   Updated: 2018/12/08 21:43:20 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixdel(void **mat)
{
	size_t	i;

	i = 0;
	if (!mat)
		return ;
	while (*(mat + i))
	{
		free(*(mat + i));
		i++;
	}
	free(*(mat + i));
	free(mat);
}
