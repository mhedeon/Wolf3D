/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 19:21:51 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/30 22:04:41 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static int	prepare_lvl3(t_wolf *wolf)
{
	wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/lvl3.mid");
	if (wolf->lvl_music != NULL)
		Mix_PlayMusic(wolf->lvl_music, -1);
	return (1);
}

static void	clear_lvl3(t_wolf *wolf)
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	if (wolf->lvl_music != NULL)
		Mix_FreeMusic(wolf->lvl_music);
	free(wolf->map);
	wolf->map = NULL;
}

static int	end_lvl3(t_wolf *wolf)
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

static int	game_lvl3(t_wolf *wolf)
{
	while (event(wolf, end_lvl3))
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
		draw_hud_lvl3(wolf);
		if (wolf->hero->health <= 0)
			return (death(wolf));
		clear_buffer(wolf);
	}
	cast_loop(wolf);
	screen_upd(wolf);
	if ((int)wolf->p_x == 4 && (int)wolf->p_y == 997)
		return (LVL4);
	return (0);
}

void		start_lvl_3(t_wolf *wolf)
{
	int		next;

	wolf->lvl_music = NULL;
	post_init(wolf);
	next = 0;
	if (map(wolf, "resource/maps/03lvl.wolfmap") && prepare_lvl3(wolf))
		next = game_lvl3(wolf);
	clear_lvl3(wolf);
	pause_frame(1000);
	if (next == LVL4)
		start_lvl_4(wolf);
}
