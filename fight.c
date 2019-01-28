/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:48:41 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 19:53:07 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void		shooot(t_wolf *wolf, t_texture *weapon, int start, int time)
{
	if ((time - start) < 75)
		draw_cursor(wolf, weapon + 1, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					1)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 1)->sur->h,
					(weapon + 1)->sur->w, (weapon + 1)->sur->h });
	else if ((time - start) < 150)
		draw_cursor(wolf, weapon + 2, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					2)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 2)->sur->h,
					(weapon + 2)->sur->w, (weapon + 2)->sur->h });
	else if ((time - start) < 225)
		draw_cursor(wolf, weapon + 3, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					3)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 3)->sur->h,
					(weapon + 3)->sur->w, (weapon + 3)->sur->h });
	else if ((time - start) < 300)
		draw_cursor(wolf, weapon + 4, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					4)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 4)->sur->h,
					(weapon + 4)->sur->w, (weapon + 4)->sur->h });
}

static void		enemy_death(t_wolf *wolf)
{
	int			x;
	int			y;

	wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].sprite = 45;
	wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].c = 0;
	Mix_PlayChannel(-1, wolf->chunk[6], 0);
	y = -2;
	while (++y < 2)
	{
		x = -2;
		while (++x < 2)
			if (!wolf->map[(wolf->m_y + y) * wolf->m_width + (wolf->m_x + x)].w
				&& !wolf->map[(wolf->m_y + y) * wolf->m_width +
				(wolf->m_x + x)].d && !wolf->map[(wolf->m_y + y) *
				wolf->m_width + (wolf->m_x + x)].s)
			{
				wolf->map[(wolf->m_y + y) * wolf->m_width +
							(wolf->m_x + x)].s = 1;
				wolf->map[(wolf->m_y + y) * wolf->m_width +
							(wolf->m_x + x)].sprite = 26;
				wolf->hero->score += 300;
				return ;
			}
	}
}

static void		damage(t_wolf *wolf, char *path)
{
	if (cast_enemy(wolf))
	{
		if (path[24] == 'K' &&
		(wolf->p_x > (wolf->m_x - 0.5) && wolf->p_x < (wolf->m_x + 1.5)) &&
		(wolf->p_y > (wolf->m_y - 0.5) && wolf->p_y < (wolf->m_y + 1.5)))
		{
			if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north > 1)
			{
				Mix_PlayChannel(-1, wolf->chunk[5], 0);
				wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north -= 1;
			}
			else
				enemy_death(wolf);
		}
		else if (path[24] == 'P')
		{
			if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north > 2)
			{
				Mix_PlayChannel(-1, wolf->chunk[5], 0);
				wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north -= 2;
			}
			else
				enemy_death(wolf);
		}
	}
}

static void		shoot(t_wolf *wolf, t_texture *weapon, int time, char *path)
{
	static int	start = 0;

	if (start == 0 && wolf->shot)
	{
		wolf->left_click = Mix_LoadWAV(path);
		if (wolf->left_click != NULL)
			Mix_PlayChannel(-1, wolf->left_click, 0);
		damage(wolf, path);
		start = SDL_GetTicks();
	}
	else
	{
		shooot(wolf, weapon, start, time);
		if ((time - start) >= 300)
		{
			wolf->shot = 0;
			start = 0;
			if (wolf->left_click != NULL)
				Mix_FreeChunk(wolf->left_click);
		}
	}
}

void			weapon(t_wolf *wolf)
{
	if (wolf->shot && wolf->weapon == 1)
		shoot(wolf, wolf->knife, SDL_GetTicks(),
				"./resource/sounds/chunk/Knife.wav");
	else if (wolf->shot && wolf->weapon == 2)
		shoot(wolf, wolf->pistol, SDL_GetTicks(),
				"./resource/sounds/chunk/Pistol.wav");
	else if (wolf->weapon == 1)
		draw_cursor(wolf, &wolf->knife[0], &(SDL_Rect){ SCREEN_WIDTH / 2 -
					wolf->knife[0].sur->w / 2, SCREEN_HEIGHT - wolf->knife
					[0].sur->h, wolf->knife[0].sur->w, wolf->knife[0].sur->h });
	else if (wolf->weapon == 2)
		draw_cursor(wolf, &wolf->pistol[0], &(SDL_Rect){ SCREEN_WIDTH / 2 -
					wolf->pistol[0].sur->w / 2, SCREEN_HEIGHT - wolf->pistol
				[0].sur->h, wolf->pistol[0].sur->w, wolf->pistol[0].sur->h });
}
