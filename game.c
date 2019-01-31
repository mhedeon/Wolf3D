/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:26:10 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:25:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		pick_up_norme(t_wolf *wolf, t_stats *hero, int s)
{
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

int				pick_up(t_wolf *wolf, t_stats *hero, int s)
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
	return (pick_up_norme(wolf, hero, s));
}

void			check_item(t_wolf *wolf)
{
	if (!wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].s)
		return ;
	wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].s =
		pick_up(wolf, wolf->hero, wolf->map[(int)wolf->p_y * wolf->m_width +
			(int)wolf->p_x].sprite);
}

void			fps(t_wolf *wolf)
{
	static int	counter = 0;

	counter += 1;
	wolf->end_frame = SDL_GetTicks();
	if ((wolf->end_frame - wolf->start_frame) < 33)
		SDL_Delay(33 - (wolf->end_frame - wolf->start_frame));
}

void			cast_loop(t_wolf *wolf)
{
	SDL_Thread	*thread[THREADS];
	t_wolf		woph[THREADS];
	int			i;

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
