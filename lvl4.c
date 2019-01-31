/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:05:27 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:26:20 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		end_lvl4(t_wolf *wolf)
{
	SDL_Event	e;

	if (cast_door(wolf) && (abs((int)wolf->p_x - wolf->m_x) +
		abs((int)wolf->p_y - wolf->m_y)) <= 1.5 &&
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 54)
	{
		if (Mix_PlayingMusic())
			Mix_HaltMusic();
		if (wolf->lvl_music != NULL)
			Mix_FreeMusic(wolf->lvl_music);
		wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/end.mid");
		if (wolf->lvl_music != NULL)
			Mix_PlayMusic(wolf->lvl_music, -1);
		wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].d = 0;
		cast_loop(wolf);
		end_game(wolf, (SDL_Rect) { 0, 0, 0, 0 });
		while (1)
			while (SDL_PollEvent(&e))
				if ((KEY == SDLK_RETURN) || (KEY == SDLK_ESCAPE))
					return (1);
		return (1);
	}
	return (0);
}

static int		prepare_lvl4(t_wolf *wolf)
{
	wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/lvl4.mid");
	if (wolf->lvl_music != NULL)
		Mix_PlayMusic(wolf->lvl_music, -1);
	return (1);
}

static void		clear_lvl4(t_wolf *wolf)
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	if (wolf->lvl_music != NULL)
		Mix_FreeMusic(wolf->lvl_music);
	free(wolf->map);
	wolf->map = NULL;
}

static int		game_lvl4(t_wolf *wolf)
{
	while (event(wolf, end_lvl4))
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
	return (0);
}

void			start_lvl_4(t_wolf *wolf)
{
	int			next;

	wolf->lvl_music = NULL;
	post_init(wolf);
	next = 0;
	if (map(wolf, "resource/maps/04lvl.wolfmap") && prepare_lvl4(wolf))
	{
		rot_dir(wolf, -90);
		rot_plane(wolf, -90);
		next = game_lvl4(wolf);
	}
	clear_lvl4(wolf);
	pause_frame(1000);
}
