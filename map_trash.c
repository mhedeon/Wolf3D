/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_trash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:35:31 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 23:20:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int				matrix_height(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

void			matrix_del(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
		free(m[i]);
	free(m[i]);
	free(m);
}

int				get_number(char a, char b)
{
	return ((a - '0') * 10 + (b - '0'));
}

int				check_digit(char *word)
{
	int i;

	i = 0;
	while (++i < (int)ft_strlen(word))
		if (word[i] < '0' || word[i] > '9')
			return (0);
	return (1);
}

int				check_player_xy(t_wolf *wolf)
{
	static int	yx[2] = { 0, 0 };

	if (wolf->p_x <= 0 || wolf->p_x >= (wolf->m_width - 1) ||
		wolf->p_y <= 0 || wolf->p_y >= (wolf->m_height - 1) ||
		wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].c == 1 ||
		wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].d == 1)
	{
		while (++(yx[0]) < (wolf->m_height - 1))
		{
			yx[1] = 0;
			while (++(yx[1]) < (wolf->m_width - 1))
				if (wolf->map[yx[0] * wolf->m_width + yx[1]].c != 1
					&& wolf->map[yx[0] * wolf->m_width + yx[1]].d != 1)
				{
					wolf->p_x = (double)(yx[1]) + 0.5;
					wolf->p_y = (double)(yx[0]) + 0.5;
					return (1);
				}
		}
		return (get_error(POSITION_ERR));
	}
	wolf->p_x += 0.5;
	wolf->p_y += 0.5;
	return (1);
}
