/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:01:29 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/28 23:23:18 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void				draw_death(t_wolf *wolf, unsigned x, unsigned y)
{
	static SDL_Color	tmp = {0x8D, 0, 0, 0xFF};
	static unsigned		a = 0;
	int					i;
	int					j;

	i = y - 1;
	while (++i < (int)(y + SQUARE))
	{
		j = x - 1;
		while (++j < (int)(x + SQUARE))
			if (((x + j) < SCREEN_WIDTH) && ((y + i) < SCREEN_HEIGHT))
			{
				if ((Uint8)(wolf->buff[y * SCREEN_WIDTH + x]
						>> 16 & 0xFF) <= 0x8D)
				{
					tmp.r = (Uint8)(wolf->buff[y * SCREEN_WIDTH + x]
							>> 16 & 0xFF) - 0x5;
					set_pixel_s(wolf, &tmp, x + j, y + i);
				}
				else
					set_pixel_s(wolf, &tmp, x + j, y + i);
			}
	}
	if (!(++a % 500))
		screen_upd(wolf);
}

static void				death_anim(t_wolf *wolf)
{
	unsigned			x;
	unsigned			y;
	unsigned			bit;
	long				value;

	value = 1;
	y = ((value & 0x000FF) - 1) * X_BOOST;
	x = ((value & 0x1FF00) >> 8) * Y_BOOST;
	bit = value & 1;
	value = value >> 1;
	if (bit)
		value ^= 0x00012000;
	draw_death(wolf, x, y);
	while (value != 1)
	{
		y = ((value & 0x000FF) - 1) * X_BOOST;
		x = ((value & 0x1FF00) >> 8) * Y_BOOST;
		bit = value & 1;
		value = value >> 1;
		if (bit)
			value ^= 0x00012000;
		draw_death(wolf, x, y);
	}
}

int						death(t_wolf *wolf)
{
	cast(wolf);
	death_anim(wolf);
	return (0);
}
