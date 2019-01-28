/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 20:27:15 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int hbp(t_wolf *wolf, t_stats *hero, int s)
{
	if (s >= 27 && s <= 30)
	{
		Mix_PlayChannel(-1, wolf->chunk[1], 0);
		hero->score += (s == 27) ? 100 : 0;
		hero->score += (s == 28) ? 500 : 0;
		hero->score += (s == 29) ? 1000 : 0;
		hero->score += (s == 30) ? 5000 : 0;
		return (0);
	}
	if (s == 26 && hero->bullet < 99)
	{
		Mix_PlayChannel(-1, wolf->chunk[0], 0);
		hero->bullet += (s == 26) ? 6 : 0;
		hero->bullet = (hero->bullet > 99) ? 99 : hero->bullet;
		return (0);
	}
	if ((s == 7 || s == 21 || s == 22 || s == 24 || s == 25)
		&& hero->health < 100)
	{
		Mix_PlayChannel(-1, wolf->chunk[2], 0);
		hero->health += (s == 24) ? 10 : 0;
		hero->health += (s == 7) ? 4 : 0;
		hero->health += (s == 25) ? 25 : 0;
		hero->health = (hero->health > 100) ? 100 : hero->health;
		return (0);
	}
	return (1);
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
	printf("qwe\n");
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
