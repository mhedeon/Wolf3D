/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:02:18 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:25:44 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_face_2(t_wolf *wolf, t_texture *face, int time, int ticks)
{
	if ((time - ticks) < 5000)
		draw_cursor(wolf, face + 5, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 5)->sur->w,
		SCREEN_HEIGHT - (face + 5)->sur->h, (face + 5)->sur->w,
		(face + 5)->sur->h });
	else if ((time - ticks) < 6000)
		draw_cursor(wolf, face + 6, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 6)->sur->w,
		SCREEN_HEIGHT - (face + 6)->sur->h, (face + 6)->sur->w,
		(face + 6)->sur->h });
	else if ((time - ticks) < 7000)
		draw_cursor(wolf, face + 7, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 7)->sur->w,
		SCREEN_HEIGHT - (face + 7)->sur->h, (face + 7)->sur->w,
		(face + 7)->sur->h });
	else if ((time - ticks) < 8000)
		draw_cursor(wolf, face + 8, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 8)->sur->w,
		SCREEN_HEIGHT - (face + 8)->sur->h, (face + 8)->sur->w,
		(face + 8)->sur->h });
}

static void		draw_face(t_wolf *wolf, t_texture *face, int time)
{
	static int	ticks = 0;

	ticks = time - ticks >= 8000 ? SDL_GetTicks() : ticks;
	if ((time - ticks) < 1000)
		draw_cursor(wolf, face + 1, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 1)->sur->w, SCREEN_HEIGHT - (face + 1)->sur->h,
		(face + 1)->sur->w, (face + 1)->sur->h });
	else if ((time - ticks) < 2000)
		draw_cursor(wolf, face + 2, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 2)->sur->w,
		SCREEN_HEIGHT - (face + 2)->sur->h, (face + 2)->sur->w,
		(face + 2)->sur->h });
	else if ((time - ticks) < 3000)
		draw_cursor(wolf, face + 3, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 3)->sur->w,
		SCREEN_HEIGHT - (face + 3)->sur->h, (face + 3)->sur->w,
		(face + 3)->sur->h });
	else if ((time - ticks) < 4000)
		draw_cursor(wolf, face + 4, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 *
		(face + 4)->sur->w,
		SCREEN_HEIGHT - (face + 4)->sur->h, (face + 4)->sur->w,
		(face + 4)->sur->h });
	else
		draw_face_2(wolf, face, time, ticks);
}

void			face(t_wolf *wolf)
{
	if (wolf->hero->health <= 15)
		draw_face(wolf, wolf->face + 60, SDL_GetTicks());
	else if (wolf->hero->health > 15 && wolf->hero->health <= 30)
		draw_face(wolf, wolf->face + 50, SDL_GetTicks());
	else if (wolf->hero->health > 30 && wolf->hero->health <= 45)
		draw_face(wolf, wolf->face + 40, SDL_GetTicks());
	else if (wolf->hero->health > 45 && wolf->hero->health <= 60)
		draw_face(wolf, wolf->face + 30, SDL_GetTicks());
	else if (wolf->hero->health > 60 && wolf->hero->health <= 75)
		draw_face(wolf, wolf->face + 20, SDL_GetTicks());
	else if (wolf->hero->health > 75 && wolf->hero->health <= 90)
		draw_face(wolf, wolf->face + 10, SDL_GetTicks());
	else if (wolf->hero->health > 90)
		draw_face(wolf, wolf->face + 0, SDL_GetTicks());
}

int				load_face(t_texture *face)
{
	int			i;
	int			j;
	char		*tmp[2];

	j = 10;
	while (j <= 70)
	{
		i = 0;
		while (++i <= 8)
		{
			tmp[0] = ft_itoa(j + i);
			tmp[1] = ft_strjoin(tmp[0], ".png");
			free(tmp[0]);
			tmp[0] = ft_strjoin("resource/img/face/", tmp[1]);
			free(tmp[1]);
			if (!load_texture(&face[j - 10 + i], tmp[0]))
			{
				free(tmp[0]);
				return (0);
			}
			free(tmp[0]);
		}
		j += 10;
	}
	return (1);
}

int				free_face(t_texture *face)
{
	int			i;
	int			j;

	j = 10;
	while (j <= 70)
	{
		i = 0;
		while (++i <= 8)
		{
			if (face[j - 10 + i].sur != NULL)
				destroy_texture(&face[j - 10 + i]);
		}
		j += 10;
	}
	return (0);
}
