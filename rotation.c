/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:10:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/23 17:26:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void		rotate(t_wolf *wolf)
{
	int		sign;

	SDL_GetMouseState(&wolf->new_mouse_x, &wolf->mouse_y);
	wolf->rs = wolf->new_mouse_x - wolf->old_mouse_x;
	sign = wolf->rs < 0.0 ? -1 : 1;
	wolf->rs = (double)(abs((int)wolf->rs) > 200 ? sign * 20.0 :
				wolf->rs / 10.0) * wolf->sens;
	rot_dir(wolf, wolf->rs);
	rot_plane(wolf, wolf->rs);
	if (wolf->new_mouse_x < 1)
	{
		SDL_WarpMouseInWindow(wolf->win, SCREEN_WIDTH - 2, wolf->mouse_y);
		wolf->new_mouse_x = SCREEN_WIDTH - 2;
	}
	if (wolf->new_mouse_x >= SCREEN_WIDTH - 1)
	{
		SDL_WarpMouseInWindow(wolf->win, 1, wolf->mouse_y);
		wolf->new_mouse_x = 1;
	}
	if (wolf->mouse_y < 1)
		SDL_WarpMouseInWindow(wolf->win, wolf->new_mouse_x, SCREEN_HEIGHT - 2);
	if (wolf->mouse_y >= SCREEN_HEIGHT - 1)
		SDL_WarpMouseInWindow(wolf->win, wolf->new_mouse_x, 1);
	wolf->old_mouse_x = wolf->new_mouse_x;
}

void		step(t_wolf *wolf, int dir)
{
	// if (wolf->map[(int)wolf->p_y * wolf->m_width +
	// 		(int)(wolf->p_x + dir * wolf->dir_x * (wolf->ms + 0.25))].w == 0 &&
	// 	wolf->map[(int)wolf->p_y * wolf->m_width +
	// 		(int)(wolf->p_x + dir * wolf->dir_x * (wolf->ms + 0.25))].s == 0)
	// 	wolf->p_x += dir * wolf->dir_x * wolf->ms;
	// if (wolf->map[(int)(wolf->p_y + dir * wolf->dir_y * (wolf->ms + 0.25)) *
	// 		wolf->m_width + (int)wolf->p_x].w == 0 &&
	// 	wolf->map[(int)(wolf->p_y + dir * wolf->dir_y * (wolf->ms + 0.25)) *
	// 		wolf->m_width + (int)wolf->p_x].s == 0)
	// 	wolf->p_y += dir * wolf->dir_y * wolf->ms;
	if (wolf->map[(int)wolf->p_y * wolf->m_width +
			(int)(wolf->p_x + dir * wolf->dir_x * (wolf->ms + 0.25))].c == 0)
		wolf->p_x += dir * wolf->dir_x * wolf->ms;
	if (wolf->map[(int)(wolf->p_y + dir * wolf->dir_y * (wolf->ms + 0.25)) *
			wolf->m_width + (int)wolf->p_x].c == 0)
		wolf->p_y += dir * wolf->dir_y * wolf->ms;
}

void		rot_dir(t_wolf *wolf, double rs)
{
	double	tmp;

	tmp = wolf->dir_x;
	wolf->dir_x = wolf->dir_x * cos(RAD(rs)) - wolf->dir_y * sin(RAD(rs));
	wolf->dir_y = tmp * sin(RAD(rs)) + wolf->dir_y * cos(RAD(rs));
}

void		rot_plane(t_wolf *wolf, double rs)
{
	double tmp;

	tmp = wolf->plane_x;
	wolf->plane_x = wolf->plane_x * cos(RAD(rs)) - wolf->plane_y * sin(RAD(rs));
	wolf->plane_y = tmp * sin(RAD(rs)) + wolf->plane_y * cos(RAD(rs));
}

void		strafe(t_wolf *wolf, int dir)
{
	double	tmp;

	tmp = wolf->ms;
	wolf->ms *= 0.75;
	rot_dir(wolf, dir * 90);
	step(wolf, GO_FORWARD);
	rot_dir(wolf, -dir * 90);
	wolf->ms = tmp;
}
