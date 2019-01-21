/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/21 22:45:13 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void			menu_anim(t_wolf *wolf, t_texture *menu, Uint32 new_time)
{
	static Uint32 old_time = 0;

	if ((new_time - old_time) < 1000)
	{
		cp_tex_to_buff(wolf, menu);
	}
	else
	{
		cp_tex_to_buff(wolf, menu + 1);
	}
	if ((new_time - old_time) >= 2000)
		old_time = new_time;
}

int				menu_event(t_wolf *wolf, t_menu *menu, int *m, SDL_Event e)
{
	if ((KEY == SDLK_DOWN) || (KEY == SDLK_UP))
		Mix_PlayChannel(1, menu->toggle, 0);
	if (e.type == SDL_QUIT)
		return (0);
	else if (KEY == SDLK_DOWN)
		*m += *m == 3 ? -3 : 1;
	else if (KEY == SDLK_UP)
		*m -= *m == 0 ? -3 : 1;
	if (KEY == SDLK_RETURN)
	{
		Mix_PlayChannel(1, menu->select, 0);
		if (*m == 0)
			return (1);
		else if (*m == 1)
			return (level(wolf, &wolf->menu));
		else if (*m == 2)
			return (show_controls());
		else
			return (0);
	}
	return (-1);
}

void			draw_cursor_in_menu(t_wolf *wolf, t_menu *menu, int m,
									char m_or_l)
{
	if (m_or_l == 'm')
	{
		if (m == 0)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { NEW_GAME });
		else if (m == 1)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { SELECT_LEVEL });
		else if (m == 2)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { CONTROLS });
		else if (m == 3)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { EXIT });
	}
	else if (m_or_l == 'l')
	{
		if (m == 0)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { LEVEL_1 });
		else if (m == 1)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { LEVEL_2 });
		else if (m == 2)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { LEVEL_3 });
		else if (m == 3)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { LEVEL_4 });
		else if (m == 4)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { BACK });
	}
}

int				m_menu(t_wolf *wolf, t_menu *menu)
{
	SDL_Event	e;
	int			m;
	int			lvl;

	m = 0;
	lvl = -1;
	Mix_PlayMusic(menu->music, 1);
	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			changes(wolf, e);
			lvl = menu_event(wolf, menu, &m, e);
		}
		menu_anim(wolf, menu->menu, SDL_GetTicks());
		draw_cursor_in_menu(wolf, menu, m, 'm');
		screen_upd(wolf);
		if (lvl > -1)
		{
			SDL_Delay(250);
			break ;
		}
	}
	Mix_HaltMusic();
	return (lvl);
}
