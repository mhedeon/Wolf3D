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

int show_controls(void)
{
	//TODO
	return (-1);
}

int level(t_wolf *wolf, t_menu *menu)
{
	//TODO
	return (-1);
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

int menu_event(t_wolf *wolf, t_menu *menu, int *m, SDL_Event e)
{
	if ((KEY == SDLK_ESCAPE) || (KEY == SDLK_DOWN) || (KEY == SDLK_UP))
		Mix_PlayChannel(-1, menu->toggle, 0);
	if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
		return (0); //TODO
	else if (KEY == SDLK_DOWN)
		*m +=* m == 3 ? -3 : 1;
	else if (KEY == SDLK_UP)
		*m -=* m == 0 ? -3 : 1;
	if (KEY == SDLK_RETURN)
	{
		Mix_PlayChannel(-1, menu->select, 0);
		if (*m == 0)
			//return (1);
			return (-1);
		else if (*m == 1)
			//return (level(wolf, &wolf->menu));
			return (-1);
		else if (*m == 2)
			//return (show_Controls());
			return (-1);
		else
			return (0);
	}
	return (-1);
}

int menu(t_wolf *wolf, t_menu *menu)
{
	SDL_Event e;
	int m;
	int lvl;

	m = 0;
	lvl = -1;
	Mix_PlayMusic(menu->music, -1);
	while (1)
	{
		if (SDL_PollEvent(&e))
			lvl = menu_event(wolf, menu, &m, e);
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
		if (lvl > -1)
		{
			SDL_Delay(250);
			break;
		}
	}
	Mix_HaltMusic();
	return (lvl);
}

int free_menu_screen(t_menu *menu)
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

int init_menu_screen(t_menu *menu)
{
	if (!load_texture(&menu->menu[0], "resource/img/menu/menu-1.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->menu[1], "resource/img/menu/menu-2.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->level[0], "resource/img/menu/level-1.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->level[1], "resource/img/menu/level-2.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->start[0], "resource/img/menu/start-1.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->start[1], "resource/img/menu/start-2.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->start[2], "resource/img/menu/start-3.jpg"))
		return (free_menu_screen(menu));
	if (!load_texture(&menu->cursor, "resource/img/menu/cursor.png"))
		return (free_menu_screen(menu));
	return (1);
}

int free_menu_sound(t_menu *menu)
{
	if (menu->music != NULL)
		Mix_FreeMusic(menu->music);
	if (menu->toggle != NULL)
		Mix_FreeChunk(menu->toggle);
	if (menu->select != NULL)
		Mix_FreeChunk(menu->select);
	if (menu->achtung != NULL)
		Mix_FreeChunk(menu->achtung);
	return (0);
}

int init_menu_sound(t_menu *menu)
{
	menu->music = Mix_LoadMUS("resource/sounds/music/menu.mid");
	if (menu->music == NULL)
		return (free_menu_sound(menu));
	menu->toggle = Mix_LoadWAV("resource/sounds/chunk/Menu Toggle.wav");
	if (menu->toggle == NULL)
		return (free_menu_sound(menu));
	menu->select = Mix_LoadWAV("resource/sounds/chunk/Menu Select.wav");
	if (menu->select == NULL)
		return (free_menu_sound(menu));
	menu->achtung = Mix_LoadWAV("resource/sounds/chunk/Achtung!.wav");
	if (menu->achtung == NULL)
		return (free_menu_sound(menu));
	Mix_Volume(-1, MIX_MAX_VOLUME);
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
