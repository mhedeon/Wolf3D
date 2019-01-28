/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:26:10 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 20:27:36 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void check_item(t_wolf *wolf)
{
	if (!wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].s)
		return ;
	wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].s =
		hbp(wolf, wolf->hero, wolf->map[(int)wolf->p_y * wolf->m_width +
			(int)wolf->p_x].sprite);
}

void fps(t_wolf *wolf)
{
	static int counter = 0;

	counter += 1;
	wolf->end_frame = SDL_GetTicks();
	if ((wolf->end_frame - wolf->start_frame) < 33)
		SDL_Delay(33 - (wolf->end_frame - wolf->start_frame));
	
}

void cast_loop(t_wolf *wolf)
{
	SDL_Thread *thread[THREADS];
	t_wolf woph[THREADS];
	int i;

	i = -1;
	while (++i < THREADS)
	{
		woph[i] = *wolf;
		woph[i].start = i * SCREEN_WIDTH / THREADS;
		woph[i].end = (i + 1) * SCREEN_WIDTH / THREADS;
		thread[i] = SDL_CreateThread((int(*)())cast, "cast",
					(void *)&woph[i]);
	}
	while (--i >= 0)
		SDL_WaitThread(thread[i], NULL);
}

int				pause_frame(t_wolf *wolf, Uint32 pause)
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
