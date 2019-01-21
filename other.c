/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:22:21 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/21 21:24:19 by mhedeon          ###   ########.fr       */
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

// void	clear_buffer(t_wolf *wolf, SDL_Color *c)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < SCREEN_HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < SCREEN_WIDTH)
// 			wolf->buff[y * SCREEN_WIDTH + x] = (255 << c->a) |
// 												152 << c->r |
// 												0 << c->g |
// 												c->b;
// 	}
// }

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

// &((SDL_Rect){50, 50, WINDOW_WIDTH, WINDOW_HEIGHT})
void	screen_upd(t_wolf *wolf)
{
	SDL_UpdateTexture(wolf->tex, NULL, wolf->buff, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(wolf->ren);
	SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
	SDL_RenderPresent(wolf->ren);
	// clear_buffer(wolf);
}

int get_cardinal(t_wolf *wolf)
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
