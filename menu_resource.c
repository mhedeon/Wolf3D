/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:27:47 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:26:38 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		free_menu_screen(t_menu *menu)
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

int		init_menu_screen(t_menu *menu)
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

int		free_menu_sound(t_menu *menu)
{
	if (menu->music != NULL)
		Mix_FreeMusic(menu->music);
	if (menu->toggle != NULL)
		Mix_FreeChunk(menu->toggle);
	if (menu->select != NULL)
		Mix_FreeChunk(menu->select);
	return (0);
}

int		init_menu_sound(t_menu *menu)
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
	return (1);
}

int		start_menu(t_wolf *wolf, t_menu *menu)
{
	int	lvl;

	lvl = -1;
	if (init_menu_screen(menu) && init_menu_sound(menu))
		lvl = m_menu(wolf, menu);
	free_menu_screen(menu);
	free_menu_sound(menu);
	return (lvl);
}
