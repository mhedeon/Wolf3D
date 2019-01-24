/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:29:40 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/23 20:13:39 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void	prepare_sprite(t_wolf *wolf, int x)
{
	wolf->sp_x = wolf->m_x + 0.5 - wolf->p_x;
	wolf->sp_y = wolf->m_y + 0.5 - wolf->p_y;
	wolf->inv = 1.0 / (wolf->plane_x * wolf->dir_y -
				wolf->plane_y * wolf->dir_x);
	wolf->spt_x = wolf->inv * (wolf->dir_y * wolf->sp_x -
				wolf->dir_x * wolf->sp_y);
	wolf->spt_y = wolf->inv * (-wolf->plane_y * wolf->sp_x +
				wolf->plane_x * wolf->sp_y);
	wolf->ssx = (int)((SCREEN_WIDTH / 2) * (1 + wolf->spt_x /
				wolf->spt_y));
	wolf->sp_h = abs((int)(SCREEN_HEIGHT / wolf->spt_y));
	wolf->sp_start = -wolf->sp_h / 2 + SCREEN_HEIGHT / 2;
	wolf->sp_end = wolf->sp_h / 2 + SCREEN_HEIGHT / 2;
	if (wolf->sp_end >= SCREEN_HEIGHT)
		wolf->sp_end = SCREEN_HEIGHT - 1;
	if (wolf->sp_start <= 0)
		wolf->sp_start = 0;
	wolf->t_x = (int)(256 * (x - (-abs((int)(SCREEN_HEIGHT /
				(wolf->spt_y))) / 2 + wolf->ssx)) * SPRITE_WIDTH /
				abs((int)(SCREEN_HEIGHT / (wolf->spt_y)))) / 256;
}

void		draw_sprite(t_wolf *wolf, int x)
{
	int		y;

	prepare_sprite(wolf, x);
	y = wolf->sp_start - 1;
	while (++y < wolf->sp_end)
	{
		wolf->t_y = (((y * 2 - SCREEN_HEIGHT + wolf->sp_h) *
					SPRITE_WIDTH) / wolf->sp_h) / 2;
		if (wolf->t_x < SPRITE_WIDTH && wolf->t_x >= 0 && wolf->t_y <
					SPRITE_HEIGHT && wolf->t_y >= 0)
		{
			get_color(&wolf->sprite[CURRENT_SPRITE], &wolf->color,
						wolf->t_x, wolf->t_y);
			set_pixel(wolf, &wolf->color, x, y);
		}
	}
}