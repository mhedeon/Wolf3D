/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:43:55 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/22 18:09:19 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int				show_controls(void)
{
	//TODO
	return (-1);
}

int				level_event(t_wolf *wolf, t_menu *menu, int *m, SDL_Event e)
{
	if ((KEY == SDLK_ESCAPE) || (KEY == SDLK_DOWN) || (KEY == SDLK_UP))
		Mix_PlayChannel(1, menu->toggle, 0);
	if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
		return (0);
	else if (KEY == SDLK_DOWN)
		*m += *m == 4 ? -4 : 1;
	else if (KEY == SDLK_UP)
		*m -= *m == 0 ? -4 : 1;
	if (KEY == SDLK_RETURN)
	{
		Mix_PlayChannel(1, menu->select, 0);
		if (*m == 0)
			return (1);
		else if (*m == 1)
			return (2);
		else if (*m == 2)
			return (3);
		else if (*m == 3)
			return (4);
		else
			return (0);
	}
	return (-1);
}

int				level(t_wolf *wolf, t_menu *menu)
{
	SDL_Event	e;
	int			m;
	int			lvl;

	m = 0;
	lvl = -1;
	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			// changes(wolf, e);
			lvl = level_event(wolf, menu, &m, e);
		}
		menu_anim(wolf, menu->level, SDL_GetTicks());
		draw_cursor_in_menu(wolf, menu, m, 'l');
		screen_upd(wolf);
		if (lvl > -1)
		{
			SDL_Delay(250);
			break ;
		}
	}
	return (lvl == 0 ? -1 : lvl);
}

void	draw_cursor(t_wolf *wolf, t_texture *tex, SDL_Rect *rect)
{
	int x;
	int y;

	y = rect->y - 1;
	while (++y < rect->y + rect->h)
	{
		x = rect->x - 1;
		while (++x < rect->x + rect->w)
		{
			get_color(tex, &wolf->color, x - rect->x, y - rect->y);
			if (!(wolf->color.r == 152 && wolf->color.g == 0
					&& wolf->color.b == 136))
				wolf->buff[y * SCREEN_WIDTH + x] = (wolf->color.a << 24) |
				wolf->color.r << 16 | wolf->color.g << 8 | wolf->color.b;
		}
	}
}
