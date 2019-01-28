/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:00:46 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 21:11:50 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int end_lvl2(t_wolf *wolf)
{
	return (0);
}

static int prepare_lvl2(t_wolf *wolf)
{
	wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/lvl1.mid");
	if (wolf->lvl_music != NULL)
		Mix_PlayMusic(wolf->lvl_music, -1);
	return (1);
}

static void clear_lvl2(t_wolf *wolf)
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	if (wolf->lvl_music != NULL)
		Mix_FreeMusic(wolf->lvl_music);
	free(wolf->map);
	wolf->map = NULL;
}

static int game_lvl2(t_wolf *wolf)
{
	while (event(wolf, end_lvl2))
	{
		if (wolf->door.opened)
			close_door(wolf);
		check_item(wolf);
		cast_loop(wolf);
		draw_x(wolf);
		weapon(wolf);
		fps(wolf);
		wolf->ms = 1 / 45.0 * 5.0;
		wolf->start_frame = wolf->end_frame;
		draw_hud(wolf);
		if (wolf->hero->health <= 0)
			return (death(wolf));
		clear_buffer(wolf);
	}
	// if (wolf->p_x == 26 && wolf->p_y == 41)
	// 	return (2);
	return (0);
}

void start_lvl_2(t_wolf *wolf)
{
	int next;

	wolf->lvl_music = NULL;
	if (map(wolf, "resource/maps/map1.wolfmap") && prepare_lvl2(wolf))
	{
		next = game_lvl2(wolf);
	}
	clear_lvl2(wolf);
}
