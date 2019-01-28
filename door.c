/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:18:00 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 23:24:39 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

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

void		draw_door(t_wolf *wolf, int x)
{
	draw_d(wolf, x);
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

void		draw_d(t_wolf *wolf, int x)
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
		wolf->t_y = ((wolf->d * WALL_HEIGHT) / wolf->draw_h) >> 8;
		wolf->t_y = wolf->t_y < 0 ? 0 : wolf->t_y;
		wolf->t_y = wolf->t_y >= WALL_HEIGHT ? WALL_HEIGHT - 1 : wolf->t_y;
		get_color(&wolf->wall[get_cardinal(wolf)],
				&wolf->color, wolf->t_x, wolf->t_y);
		set_pixel(wolf, &wolf->color, x, y);
	}
}

void		open_door(t_wolf *wolf)
{
	if (cast_door(wolf) && (abs((int)wolf->p_x - wolf->m_x) +
			abs((int)wolf->p_y - wolf->m_y)) <= 1.5 &&
			wolf->door.opened == 0)
	{
		if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 9 ||
			wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 3)
			Mix_PlayChannel(-1, wolf->chunk[4], 0);
		else
			Mix_PlayChannel(-1, wolf->chunk[3], 0);
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].d = 0;
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].c = 0;
		wolf->door.x = wolf->m_x;
		wolf->door.y = wolf->m_y;
		if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 52 ||
			wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 54 ||
			wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 55)
			wolf->door.opened = 1;
	}
}

void		close_door(t_wolf *wolf)
{
	if ((wolf->p_x > (wolf->door.x - 1.0) && wolf->p_x < (wolf->door.x + 2.0))
		&&
		(wolf->p_y > (wolf->door.y - 1.0) && wolf->p_y < (wolf->door.y + 2.0)))
		return ;
	Mix_PlayChannel(-1, wolf->chunk[3], 0);
	wolf->map[wolf->door.y * wolf->m_width + wolf->door.x].d = 1;
	wolf->map[wolf->door.y * wolf->m_width + wolf->door.x].c = 1;
	wolf->door.opened = 0;
}
