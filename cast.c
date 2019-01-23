/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:49:49 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/23 21:01:22 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void	prepare(t_wolf *wolf, int x)
{
	wolf->cam_x = 2.0 * x / (double)SCREEN_WIDTH - 1;
	wolf->ray_dir_x = wolf->dir_x + wolf->plane_x * wolf->cam_x;
	wolf->ray_dir_y = wolf->dir_y + wolf->plane_y * wolf->cam_x;
	wolf->m_x = (int)wolf->p_x;
	wolf->m_y = (int)wolf->p_y;
	wolf->d_x = fabs(1.0 / wolf->ray_dir_x);
	wolf->d_y = fabs(1.0 / wolf->ray_dir_y);
	wolf->hit = 0;
	wolf->step_x = wolf->ray_dir_x < 0.0 ? -1 : 1;
	wolf->step_y = wolf->ray_dir_y < 0.0 ? -1 : 1;
	wolf->side_x = wolf->d_x * ((wolf->ray_dir_x < 0.0) ?
		(wolf->p_x - (double)wolf->m_x) :
		((double)wolf->m_x + 1.0 - wolf->p_x));
	wolf->side_y = wolf->d_y * ((wolf->ray_dir_y < 0.0) ?
		(wolf->p_y - (double)wolf->m_y) :
		((double)wolf->m_y + 1.0 - wolf->p_y));
}

static void	ty_for_norm(t_wolf *wolf)
{
	if (wolf->side_x < wolf->side_y)
	{
		wolf->side_x += wolf->d_x;
		wolf->m_x += wolf->step_x;
		wolf->side = wolf->ray_dir_x < 0 ? EAST : WEST;
	}
	else
	{
		wolf->side_y += wolf->d_y;
		wolf->m_y += wolf->step_y;
		wolf->side = wolf->ray_dir_y < 0 ? NORTH : SOUTH;
	}
}

void		cast(t_wolf *wolf)
{
	int		x;

	x = wolf->start - 1;
	while (++x < wolf->end)
	{
		prepare(wolf, x);
		while (1)
		{
			ty_for_norm(wolf);
			if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].w)
			{
				draw(wolf, x);
				break ;
			}
			else if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].d &&
						wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].c)
			{
				draw_door(wolf, x);
				break ;
			}
			else if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].s)
				draw_sprite(wolf, x);
		}
	}
}

int			cast_door(t_wolf *wolf)
{
	int		x;

	x = SCREEN_WIDTH / 2;
	prepare(wolf, x);
	while (1)
	{
		if (wolf->side_x < wolf->side_y)
		{
			wolf->side_x += wolf->d_x;
			wolf->m_x += wolf->step_x;
			wolf->side = wolf->ray_dir_x < 0 ? EAST : WEST;
		}
		else
		{
			wolf->side_y += wolf->d_y;
			wolf->m_y += wolf->step_y;
			wolf->side = wolf->ray_dir_y < 0 ? NORTH : SOUTH;
		}
		if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].w)
			return (0);
		else if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].d)
			return (1);
	}
}
