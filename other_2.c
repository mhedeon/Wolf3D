/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:54:21 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 22:55:17 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int		get_cardinal(t_wolf *wolf)
{
	if (wolf->side == NORTH)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north);
	if (wolf->side == SOUTH)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].south);
	if (wolf->side == WEST)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].west);
	if (wolf->side == EAST)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].east);
	return (0);
}

void	draw_x(t_wolf *wolf)
{
	int	x;
	int	y;
	int	i;

	wolf->color.a = 255;
	wolf->color.r = 255;
	wolf->color.g = 255;
	wolf->color.b = 255;
	i = -1;
	x = SCREEN_WIDTH / 2 - 12;
	y = SCREEN_HEIGHT / 2 - 12;
	while (++i < 25)
	{
		set_pixel_s(wolf, &wolf->color, x++, SCREEN_HEIGHT / 2);
		set_pixel_s(wolf, &wolf->color, SCREEN_WIDTH / 2, y++);
	}
}
