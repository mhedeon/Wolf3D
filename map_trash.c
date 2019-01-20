/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_trash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:35:31 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/20 19:41:52 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int		matrix_height(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

void	matrix_del(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
		free(m[i]);
	free(m[i]);
	free(m);
}

int		get_number(char a, char b)
{
	return ((a - '0') * 10 + (b - '0'));
}

int		check_digit(char *word)
{
	int i;

	i = 0;
	while (++i < ft_strlen(word))
		if (word[i] < '0' || word[i] > '9')
			return (0);
	return (1);
}
