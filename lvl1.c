/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:46:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/21 21:59:57 by mhedeon          ###   ########.fr       */
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

void start_lvl_1(t_wolf *wolf)
{
	wolf->lvl_music = NULL;
	if (map(wolf, "resource/maps/01lvl.wolfmap") && prepare_lvl(wolf))
	{
		raycast(wolf);
	}
	clear_lvl(wolf);
}
