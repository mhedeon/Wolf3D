/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/10 17:52:40 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int pause(t_wolf *wolf, Uint32 pause)
{
	SDL_Event	event;
	Uint32	time;

	time = SDL_GetTicks();
	while ((SDL_GetTicks() - time) < pause)
	{
		if (SDL_PollEvent(&event))
			;
		SDL_Delay(1);
	}
	return (0);
}

int free_start(t_texture *start, Mix_Chunk *achtung)
{
	if (start->sur != NULL)
		destroy_texture(start);
	if ((start + 1)->sur != NULL)
		destroy_texture(start + 1);
	if ((start + 2)->sur != NULL)
		destroy_texture(start + 2);
	if (achtung != NULL)
		Mix_FreeChunk(achtung);
	return (0);
}

int init_start(t_texture *start, Mix_Chunk *achtung)
{
	start->sur = NULL;
	(start + 1)->sur = NULL;
	(start + 2)->sur = NULL;
	if (!load_texture(start, "resource/img/menu/start-1.jpg"))
		return (free_start(start, achtung));
	if (!load_texture(start + 1, "resource/img/menu/start-2.jpg"))
		return (free_start(start, achtung));
	if (!load_texture(start + 2, "resource/img/menu/start-3.jpg"))
		return (free_start(start, achtung));
	if (achtung == NULL)
		return (free_start(start, achtung));
	return (1);
}

void start_anim(t_wolf *wolf)
{
	t_texture start[3];
	Mix_Chunk *achtung;

	achtung = Mix_LoadWAV("resource/sounds/chunk/Achtung!.wav");
	if (init_start(start, achtung))
	{
		Mix_PlayChannel(-1, achtung, 0);
		cp_tex_to_buff(wolf, &start[0]);
		screen_upd(wolf);
		screen_upd(wolf);
		pause(wolf, 200);
		cp_tex_to_buff(wolf, &start[1]);
		screen_upd(wolf);
		screen_upd(wolf);
		pause(wolf, 200);
		cp_tex_to_buff(wolf, &start[2]);
		screen_upd(wolf);
		screen_upd(wolf);
		pause(wolf, 2000);
		free_start(start, achtung);
	}
}

int			main(int ac, char **av)
{
	t_wolf *wolf;
	int lvl;
	
	wolf = malloc(sizeof(t_wolf));
	pre_init(wolf);
	intro(wolf);
	while (1)
	{
		if (init_menu_screen(&wolf->menu) &&
			init_menu_sound(&wolf->menu))
		{
			lvl = menu(wolf, &wolf->menu);
			free_menu_screen(&wolf->menu);
			free_menu_sound(&wolf->menu);
		}
		else
			break ;
		if (lvl == 0)
			break ;
	}


	//system("leaks test");
	return (0);
}