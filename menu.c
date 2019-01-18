/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/10 17:52:40 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void level(t_wolf *wolf, t_menu *menu)
{

}

void menu_anim(t_wolf *wolf, t_menu *menu, Uint32 new_time)
{
	static Uint32 old_time = 0;

	if ((new_time - old_time) < 1000)
	{
		cp_tex_to_buff(wolf, &menu->menu[0]);
	}
	else
	{
		cp_tex_to_buff(wolf, &menu->menu[1]);
	}
	if ((new_time - old_time) >= 2000)
		old_time = new_time;
}

void menu(t_wolf *wolf, t_menu *menu)
{
	SDL_Event e;
	int m;
	Mix_Music *menu_m;
	Mix_Chunk *ch[3];

	m = 0;
	ch[0] = Mix_LoadWAV("resource/sounds/chunk/Menu Toggle.wav");
	ch[1] = Mix_LoadWAV("resource/sounds/chunk/Menu Select.wav");
	ch[2] = Mix_LoadWAV("resource/sounds/chunk/Achtung!.wav");
	menu_m = Mix_LoadMUS("resource/sounds/music/menu.mid");
	if (menu_m != NULL)
		Mix_PlayMusic(menu_m, -1);
	while (1)
	{
		
		if (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
				e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break;
			else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				Mix_PlayChannel(-1, ch[0], 0);
				m += m == 3 ? -3 : 1;
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				Mix_PlayChannel(-1, ch[0], 0);
				m -= m == 0 ? -3 : 1;
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				if (m == 0)
				{
					Mix_PlayChannel(-1, ch[1], 0);
					SDL_Delay(150);
					Mix_PlayChannel(-1, ch[2], 0);
					ng_anim(wolf);
				}
				else if (m == 1)
				{
					Mix_PlayChannel(-1, ch[1], 0);
					level(wolf, menu);
				}
				else if (m == 2)
					Mix_PlayChannel(-1, ch[1], 0); //TODO
				else if (m == 3)
				{
					Mix_PlayChannel(-1, ch[1], 0);
					SDL_Delay(600);
					break;
				}
			}
		menu_anim(wolf, menu, SDL_GetTicks());
		if (m == 0)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { NEW_GAME });
		else if (m == 1)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { SELECT_LEVEL });
		else if (m == 2)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { CONTROLS });
		else if (m == 3)
			draw_cursor(wolf, &menu->cursor, &(SDL_Rect) { EXIT });
		
		screen_upd(wolf);
	}
	Mix_HaltMusic();
	Mix_FreeMusic(menu_m);
	Mix_FreeChunk(ch[0]);
	Mix_FreeChunk(ch[1]);
	Mix_FreeChunk(ch[2]);
}

int free_menu(t_menu *menu)
{
	if (menu->menu[0].sur != NULL)
		destroy_texture(&menu->menu[0]);
	if (menu->menu[1].sur != NULL)
		destroy_texture(&menu->menu[1]);
	if (menu->level[0].sur != NULL)
		destroy_texture(&menu->level[0]);
	if (menu->level[1].sur != NULL)
		destroy_texture(&menu->level[1]);
	if (menu->start[0].sur != NULL)
		destroy_texture(&menu->start[0]);
	if (menu->start[1].sur != NULL)
		destroy_texture(&menu->start[1]);
	if (menu->start[2].sur != NULL)
		destroy_texture(&menu->start[2]);
	if (menu->cursor.sur != NULL)
		destroy_texture(&menu->cursor);
	return (0);
}

int init_menu(t_menu *menu)
{
	if (!load_texture(&menu->menu[0], "resource/img/menu/menu-1.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->menu[1], "resource/img/menu/menu-2.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->level[0], "resource/img/menu/level-1.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->level[1], "resource/img/menu/level-2.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->start[0], "resource/img/menu/start-1.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->start[1], "resource/img/menu/start-2.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->start[2], "resource/img/menu/start-3.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->cursor, "resource/img/menu/cursor.png"))
		return (free_menu(menu));
	return (1);
}

void draw_cursor(t_wolf *wolf, t_texture *tex, SDL_Rect *rect)
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
			if (!(wolf->color.r == 152 && wolf->color.g == 0 && wolf->color.b == 136))
				wolf->buff[y * SCREEN_WIDTH + x] = (wolf->color.a << 24) |
				wolf->color.r << 16 |
				wolf->color.g << 8 |
				wolf->color.b;
		}
	}
}
