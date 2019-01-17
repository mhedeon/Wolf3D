/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/10 17:52:40 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void		cp_tex_to_buff(t_wolf *wolf, t_texture *tex)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			wolf->buff[y * SCREEN_WIDTH + x] = 0;
	}
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			wolf->buff[y * SCREEN_WIDTH + x] = tex->pixels[y * tex->sur->w + x];
	}
}

static void intro_anim_2(t_wolf *wolf, t_texture *intro, Uint32 time)
{
	int x;
	int y;
	double boost;

	boost = (6000 - (time > 6000 ? 6000 :
		time)) / 6000.0;
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			get_color(intro, &wolf->color, x, y);
			wolf->color.r = (Uint8)(wolf->color.r * boost);
			wolf->color.g = (Uint8)(wolf->color.g * boost);
			wolf->color.b = (Uint8)(wolf->color.b * boost);
			set_pixel_s(wolf, &wolf->color, x, y);
		}
	}
}

void		intro_anim(t_wolf *wolf, t_texture *intro)
{
	Uint32 old;
	Uint32 cur;
	SDL_Event e;

	old = SDL_GetTicks();
	cur = old;
	while ((cur - old) < 6000)
	{
		cur = SDL_GetTicks();
		intro_anim_2(wolf, intro, cur - old);
		screen_upd(wolf);
		if (SDL_PollEvent(&e))
			if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				break;
	}
}

void		intro(t_wolf *wolf)
{
	t_texture intro;

	if (load_texture(&intro, "resource/img/menu/intro-1.jpg"))
	{
		cp_tex_to_buff(wolf, &intro);
		intro_anim(wolf, &intro);
		destroy_texture(&intro);
	}
	if (load_texture(&intro, "resource/img/menu/intro-2.jpg"))
	{
		cp_tex_to_buff(wolf, &intro);
		intro_anim(wolf, &intro);
		destroy_texture(&intro);
	}
}
