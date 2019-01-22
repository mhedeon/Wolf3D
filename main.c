/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/22 17:58:26 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"





int hbp(t_stats *hero, int s)
{
	if (s >= 27 && s <= 30)
	{
		hero->score += (s == 27) ? 100 : 0;
		hero->score += (s == 28) ? 500 : 0;
		hero->score += (s == 29) ? 1000 : 0;
		hero->score += (s == 30) ? 5000 : 0;
		return (0);
	}
	if (s == 26 && hero->bullet < 99)
	{
		hero->bullet += (s == 26) ? 8 : 0;
		hero->bullet = (hero->bullet > 99) ? 99 : hero->bullet;
		return (0);
	}
	if ((s == 7 || s == 21 || s == 22 || s == 24 || s == 25) && hero->healh < 100)
	{
		hero->healh += (s == 24) ? 10 : 0;
		hero->healh += (s == 7) ? 4 : 0;
		hero->healh += (s == 25) ? 25 : 0;
		hero->healh = (hero->healh > 100) ? 100 : hero->healh;
		return (0);
	}
	return (1);
}

void check_item(t_wolf *wolf)
{
	if (!wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].s)
		return ;
	wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].s =
		hbp(wolf->hero, wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].sprite);
}

// void fps(t_wolf *wolf)
// {
// 	static int counter = 0;
// 	static int i = 0;
// 	static int average = 0;

// 	counter++;
// 	wolf->end_frame = SDL_GetTicks();
// 	// printf("c: %f\n", wolf->end_frame - wolf->start_frame);
// 	if ((wolf->end_frame - wolf->start_frame) >= 1000)
// 	{
// 		wolf->fps = counter;
// 		// if (++i > 1)
// 		// {
// 		// 	wolf->fps = (average + counter) / 2;
// 		// 	i = 0;
// 		// 	average = 0;
// 		// }
// 		// else
// 		// 	average += counter;
// 		counter = 0;
// 		wolf->start_frame = wolf->end_frame;
// 		printf("FPS: %f\n", wolf->fps);
// 	}
// }

void fps(t_wolf *wolf)
{
	static int counter = 0;

	counter += 1;
	wolf->end_frame = SDL_GetTicks();
	if ((wolf->end_frame - wolf->start_frame) < 33)
		SDL_Delay(33 - (wolf->end_frame - wolf->start_frame));
	
}

void raycast(t_wolf *wolf)
{
	double ms = 1 / wolf->fps * 5.0;
	wolf->start_frame = SDL_GetTicks();
	while (event(wolf))
	{
		if (wolf->door.opened)
			close_door(wolf);
		check_item(wolf);

		SDL_Thread *thread[THREADS];
		t_wolf woph[THREADS];
		
		for (int i = 0; i < THREADS; i++)
		{
			woph[i] = *wolf;
			woph[i].start = i * SCREEN_WIDTH / THREADS;
			woph[i].end = (i + 1) * SCREEN_WIDTH / THREADS;
			thread[i] = SDL_CreateThread((int(*)())cast, "cast", (void *)&woph[i]);
		}
		for (int i = 0; i < THREADS; i++)
			SDL_WaitThread(thread[i], NULL);
		// wolf->start = 0;
		// wolf->end = SCREEN_WIDTH;
		cast(wolf);
		draw_x(wolf);
		SDL_UpdateTexture(wolf->tex, NULL, wolf->buff, SCREEN_WIDTH * sizeof(Uint32));
		screen_upd(wolf);
		// clear_buffer(wolf);
	

		// wolf->end_frame = SDL_GetTicks();
		// wolf->frame = (wolf->end_frame - wolf->start_frame) / 1000.0;
		// wolf->fps = 1.0 / wolf->frame;
		fps(wolf);
		wolf->ms = 1 / 30.0 * 5.0;
		// wolf->ms = (wolf->ms + ms) / 2;
		// ms = wolf->ms;
		// wolf->rs = 1 / wolf->fps * 150.0;
		// printf("FPS: %f\n", wolf->fps);
		wolf->start_frame = wolf->end_frame;

		screen_upd(wolf);
		clear_buffer(wolf);
	}
	/*wolf->color.a = 0xFF;
	wolf->color.r = 0x8D;//0x8D;
	wolf->color.g = 0;
	wolf->color.b = 0;*/
	// death_anim(wolf);
	// SDL_Delay(5000);
	// close_win(wolf);
}





void select_lvl(t_wolf *wolf, int lvl)
{
	post_init(wolf);
	if (lvl == 1)
		start_lvl_1(wolf);
	else if (lvl == 2)
		// start_lvl_2(wolf); TODO
		;
	else if(lvl == 3)
		// start_lvl_3(wolf); TODO
		;
	else if (lvl == 4)
		// start_lvl_4(wolf); TODO
		;
	free_garbage_2(wolf);
}

int			main(void)
{
	t_wolf *wolf;
	int lvl;
	
	wolf = malloc(sizeof(t_wolf));
	pre_init(wolf);
	Mix_Volume(1, SDL_MIX_MAXVOLUME / 2);
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME / 2);
	wolf->volume = (SDL_MIX_MAXVOLUME / 2) - 4;
	printf("%d\n", wolf->volume);
	intro(wolf);
	while (1)
	{
		lvl = start_menu(wolf, &wolf->menu);
		select_lvl(wolf, lvl);
		if (lvl < 1)
			break ;
	}
	

	free_garbage_1(wolf);
	system("leaks Wolf3D");
	return (0);
}


/*

SDL_Event e;
while (1)
{
	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
			break;
		else if (KEY == SDLK_f && e.key.keysym.mod != KMOD_LSHIFT)
			SDL_SetWindowFullscreen(wolf->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else if (e.key.keysym.mod == KMOD_LSHIFT && KEY == SDLK_f)
			SDL_SetWindowFullscreen(wolf->win, 0);
	}
}
*/