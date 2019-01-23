/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:46:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/23 21:29:06 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static int  prepare_lvl(t_wolf *wolf)
{
	wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/lvl1.mid");
	if (wolf->lvl_music != NULL)
		Mix_PlayMusic(wolf->lvl_music, -1);
	return (1);
}

static void clear_lvl(t_wolf *wolf)
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	if (wolf->lvl_music != NULL)
		Mix_FreeMusic(wolf->lvl_music);
}

static void game(t_wolf *wolf)
{
	while (event(wolf))
	{
		
		if (wolf->door.opened)
			close_door(wolf);
		check_item(wolf);
		cast_loop(wolf);
		draw_x(wolf);
		screen_upd(wolf);
		fps(wolf);
		wolf->ms = 1 / 30.0 * 5.0;
		wolf->start_frame = wolf->end_frame;
		screen_upd(wolf);
		clear_buffer(wolf);
	}
}

void start_lvl_1(t_wolf *wolf)
{
	wolf->lvl_music = NULL;
	if (map(wolf, "resource/maps/01lvl.wolfmap") && prepare_lvl(wolf))
	{
		game(wolf);
	}
	clear_lvl(wolf);
}
