/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:54:21 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 19:03:48 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				get_cardinal(t_wolf *wolf)
{
	if (wolf->side == NORTH)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north);
	if (wolf->side == SOUTH)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].south);
	if (wolf->side == WEST)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].west);
	if (wolf->side == EAST)
		return (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].east);
	return (0);
}

void			draw_x(t_wolf *wolf)
{
	int			x;
	int			y;
	int			i;

	wolf->color.a = 255;
	wolf->color.r = 255;
	wolf->color.g = 255;
	wolf->color.b = 255;
	i = -1;
	x = SCREEN_WIDTH / 2 - 12;
	y = SCREEN_HEIGHT / 2 - 12;
	while (++i < 25)
	{
		set_pixel_s(wolf, &wolf->color, x++, SCREEN_HEIGHT / 2);
		set_pixel_s(wolf, &wolf->color, SCREEN_WIDTH / 2, y++);
	}
}

void			end_game(t_wolf *wolf, SDL_Rect r)
{
	SDL_Surface	*sur;
	SDL_Texture	*message;

	SDL_UpdateTexture(wolf->tex, NULL, wolf->buff,
					SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(wolf->ren);
	SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
	sur = TTF_RenderText_Solid(wolf->font, "The End ???",
			(SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = r.x / 1.5;
	r.h = r.x / 2;
	SDL_RenderCopy(wolf->ren, message, NULL,
				&(SDL_Rect) { (r.x - r.w) / 2, (r.y - r.h) / 2, r.w, r.h});
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
	SDL_RenderPresent(wolf->ren);
}

void			dist_lvl_3(t_wolf *wolf, SDL_Rect r)
{
	char		*tmp;
	SDL_Surface	*sur;
	SDL_Texture	*message;

	tmp = ft_itoa((int)sqrt((4.0 - wolf->p_x) * (4.0 - wolf->p_x) +
						(1000.0 - wolf->p_y) * (1000.0 - wolf->p_y)) - 1);
	sur = TTF_RenderText_Solid(wolf->font, tmp,
			(SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = r.x / 2;
	r.h = r.x / 7;
	SDL_RenderCopy(wolf->ren, message, NULL,
				&(SDL_Rect) { (r.x - r.w) / 2, r.h, r.w, r.h});
	free(tmp);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

void			check_horizontal(t_wolf *wolf)
{
	int			x;

	x = -1;
	while (++x < wolf->m_width)
	{
		if (wolf->map[0 * wolf->m_width + x].w != 1 ||
			wolf->map[0 * wolf->m_width + x].c != 1)
		{
			wolf->map[0 * wolf->m_width + x].w = 1;
			wolf->map[0 * wolf->m_width + x].c = 1;
		}
		if (wolf->map[(wolf->m_height - 1) * wolf->m_width + x].w != 1 ||
			wolf->map[(wolf->m_height - 1) * wolf->m_width + x].c != 1)
		{
			wolf->map[(wolf->m_height - 1) * wolf->m_width + x].w = 1;
			wolf->map[(wolf->m_height - 1) * wolf->m_width + x].c = 1;
		}
	}
}
