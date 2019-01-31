/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:58:00 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:25:33 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	prepare(t_wolf *wolf)
{
	wolf->dist = !(wolf->side % 2) ? (((double)wolf->m_x - wolf->p_x +
		(1 - wolf->step_x) / 2) / wolf->ray_dir_x) :
		(((double)wolf->m_y - wolf->p_y + (1 - wolf->step_y) / 2)
		/ wolf->ray_dir_y);
	wolf->draw_h = wolf->dist == 0 ? 0 : (int)(SCREEN_HEIGHT / wolf->dist);
	wolf->draw_start = -wolf->draw_h / 2 + SCREEN_HEIGHT / 2;
	wolf->draw_start = (wolf->draw_start < 0) ? 0 : wolf->draw_start;
	wolf->draw_end = wolf->draw_start + wolf->draw_h;
	wolf->draw_end = (wolf->draw_end >= SCREEN_HEIGHT) ?
		SCREEN_HEIGHT : wolf->draw_end;
}

void		draw(t_wolf *wolf, int x)
{
	draw_wall(wolf, x);
	if (!(wolf->side % 2) && wolf->ray_dir_x > 0)
	{
		wolf->f_x = wolf->m_x;
		wolf->f_y = wolf->m_y + wolf->w_x;
	}
	else if (!(wolf->side % 2) && wolf->ray_dir_x < 0)
	{
		wolf->f_x = wolf->m_x + 1.0;
		wolf->f_y = wolf->m_y + wolf->w_x;
	}
	else if ((wolf->side % 2) && wolf->ray_dir_y > 0)
	{
		wolf->f_x = wolf->m_x + wolf->w_x;
		wolf->f_y = wolf->m_y;
	}
	else
	{
		wolf->f_x = wolf->m_x + wolf->w_x;
		wolf->f_y = wolf->m_y + 1.0;
	}
	draw_floor(wolf, x);
}

void		draw_wall(t_wolf *wolf, int x)
{
	int		y;

	prepare(wolf);
	wolf->w_x = !(wolf->side % 2) ? (wolf->p_y + wolf->dist * wolf->ray_dir_y) :
		(wolf->p_x + wolf->dist * wolf->ray_dir_x);
	wolf->w_x -= floor(wolf->w_x);
	wolf->t_x = (int)(wolf->w_x * (double)WALL_WIDTH);
	if (!(wolf->side % 2) && !(wolf->ray_dir_x > 0))
		wolf->t_x = WALL_WIDTH - wolf->t_x - 1;
	if (wolf->side % 2 && !(wolf->ray_dir_y < 0))
		wolf->t_x = WALL_WIDTH - wolf->t_x - 1;
	y = wolf->draw_start - 2;
	while (++y <= wolf->draw_end)
	{
		wolf->d = y * 256 - SCREEN_HEIGHT * 128 + wolf->draw_h * 128;
		wolf->t_y = wolf->draw_h == 0 ? 0 : ((wolf->d * WALL_HEIGHT)
			/ wolf->draw_h) >> 8;
		wolf->t_y = wolf->t_y < 0 ? 0 : wolf->t_y;
		wolf->t_y = wolf->t_y >= WALL_HEIGHT ? WALL_HEIGHT - 1 : wolf->t_y;
		get_color(&wolf->wall[get_cardinal(wolf)],
				&wolf->color, wolf->t_x, wolf->t_y);
		set_pixel(wolf, &wolf->color, x, y);
	}
}

void		draw_floor(t_wolf *wolf, int x)
{
	int		y;
	double	f1_x;
	double	f1_y;

	y = wolf->draw_end;
	while (++y <= SCREEN_HEIGHT)
	{
		wolf->w = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
		wolf->w = wolf->w / wolf->dist;
		f1_x = wolf->w * wolf->f_x + (1.0 - wolf->w) * wolf->p_x;
		f1_y = wolf->w * wolf->f_y + (1.0 - wolf->w) * wolf->p_y;
		wolf->fc_x = (int)(f1_x * FLOOR_WIDTH) % FLOOR_WIDTH;
		wolf->fc_y = (int)(f1_y * FLOOR_HEIGHT) % FLOOR_HEIGHT;
		get_color(&wolf->wall[CURRENT_FLOOR],
				&wolf->color, wolf->fc_x, wolf->fc_y);
		set_pixel(wolf, &wolf->color, x, y);
		wolf->fc_x = (int)(f1_x * CEIL_WIDTH) % CEIL_WIDTH;
		wolf->fc_y = (int)(f1_y * CEIL_HEIGHT) % CEIL_HEIGHT;
		get_color(&wolf->wall[CURRENT_CEIL],
				&wolf->color, wolf->fc_x, wolf->fc_y);
		set_pixel(wolf, &wolf->color, x, SCREEN_HEIGHT - y);
	}
}
