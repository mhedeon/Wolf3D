/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:22:21 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 22:56:06 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	get_color(t_texture *tex, SDL_Color *color, int x, int y)
{
	color->a = (Uint8)(tex->pixels[y * tex->sur->w + x] >> 24);
	color->r = (Uint8)(tex->pixels[y * tex->sur->w + x] >> 16 & 0xFF);
	color->g = (Uint8)(tex->pixels[y * tex->sur->w + x] >> 8 & 0xFF);
	color->b = (Uint8)(tex->pixels[y * tex->sur->w + x] & 0xFF);
}

void	set_pixel(t_wolf *wolf, SDL_Color *color, int x, int y)
{
	if ((wolf->buff[y * SCREEN_WIDTH + x] >> 16 & 0xFF) == 152 &&
		(wolf->buff[y * SCREEN_WIDTH + x] >> 8 & 0xFF) == 0 &&
		(wolf->buff[y * SCREEN_WIDTH + x] & 0xFF) == 136)
		wolf->buff[y * SCREEN_WIDTH + x] = (color->a << 24) |
										color->r << 16 |
										color->g << 8 |
										color->b;
}

void	set_pixel_s(t_wolf *wolf, SDL_Color *color, int x, int y)
{
	wolf->buff[y * SCREEN_WIDTH + x] = (color->a << 24) |
										color->r << 16 |
										color->g << 8 |
										color->b;
}

void	clear_buffer(t_wolf *wolf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			wolf->buff[y * SCREEN_WIDTH + x] = (255 << 24) |
												152 << 16 |
												0 << 8 |
												136;
	}
}

void	screen_upd(t_wolf *wolf)
{
	SDL_UpdateTexture(wolf->tex, NULL, wolf->buff,
					SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(wolf->ren);
	SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
	SDL_RenderPresent(wolf->ren);
}
