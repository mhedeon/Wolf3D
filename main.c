/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 23:25:33 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int				pause_frame(Uint32 pause)
{
	SDL_Event	event;
	Uint32		time;

	time = SDL_GetTicks();
	while ((SDL_GetTicks() - time) < pause)
	{
		if (SDL_PollEvent(&event))
			;
		SDL_Delay(1);
	}
	return (0);
}


static int select_lvl(t_wolf *wolf, int lvl)
{
	post_init(wolf);
	if (lvl == LVL1)
		start_lvl_1(wolf);
	else if (lvl == LVL2)
		start_lvl_2(wolf);
	else if(lvl == LVL3)
		// start_lvl_3(wolf); TODO
		;
	else if (lvl == LVL4)
		// start_lvl_4(wolf); TODO
		;
	return (1);
}

int			main(void)
{
	t_wolf *wolf;
	int lvl;
	
	wolf = malloc(sizeof(t_wolf));
	if (wolf == NULL)
		return (get_error(WOLF_ERR));
	if (pre_init(wolf))
	{
		Mix_Volume(-1, SDL_MIX_MAXVOLUME / 2);
		Mix_VolumeMusic(SDL_MIX_MAXVOLUME / 2);
		wolf->volume = (SDL_MIX_MAXVOLUME / 2) - 4;
		intro(wolf);
		while (1)
		{
			lvl = start_menu(wolf, &wolf->menu);
			select_lvl(wolf, lvl);
			if (lvl < 1)
				break ;
		}
	}
	free_garbage_1(wolf);
	system("leaks Wolf3D");
	return (0);
}
