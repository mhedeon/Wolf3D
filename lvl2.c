/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:00:46 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 18:44:37 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	end_lvl2(t_wolf *wolf)
{
	if (cast_door(wolf) && (abs((int)wolf->p_x - wolf->m_x) +
		abs((int)wolf->p_y - wolf->m_y)) <= 1.5 &&
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 57)
	{
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north = 58;
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].south = 58;
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].west = 58;
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].east = 58;
		return (1);
	}
	return (0);
}

static int	prepare_lvl2(t_wolf *wolf)
{
	wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/lvl2.mid");
	if (wolf->lvl_music != NULL)
		Mix_PlayMusic(wolf->lvl_music, -1);
	return (1);
}

static void	clear_lvl2(t_wolf *wolf)
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	if (wolf->lvl_music != NULL)
		Mix_FreeMusic(wolf->lvl_music);
	free(wolf->map);
	wolf->map = NULL;
}

static int	game_lvl2(t_wolf *wolf)
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
	cast_loop(wolf);
	screen_upd(wolf);
	if ((int)wolf->p_x == 2 && (int)wolf->p_y == 49)
		return (LVL3);
	return (0);
}

void		start_lvl_2(t_wolf *wolf)
{
	int		next;

	wolf->lvl_music = NULL;
	post_init(wolf);
	next = 0;
	if (map(wolf, "resource/maps/02lvl.wolfmap") && prepare_lvl2(wolf))
	{
		rot_dir(wolf, -91);
		rot_plane(wolf, -91);
		next = game_lvl2(wolf);
	}
	clear_lvl2(wolf);
	pause_frame(1000);
	if (next == LVL3)
		start_lvl_3(wolf);
}
