/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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
	y = - 1;
	while (++y < SCREEN_HEIGHT)
	{
		x =  - 1;
		while (++x < SCREEN_WIDTH)
			wolf->buff[y * SCREEN_WIDTH + x] = tex->pixels[y * tex->sur->w + x];
	}
}

void		intro_anim(t_wolf *wolf, t_texture *intro)
{
	int	x;
	int	y;
	int	count;

	count = 256;
	while (count > 0)
	{
		count -= 1;
		y = 199;
		while (++y < SCREEN_HEIGHT)
		{
			x = 199;
			while (++x < 900)
			{
				get_color(intro, &wolf->color, x, y);
				wolf->color.r = wolf->color.r > 0 ? (Uint8)(wolf->color.r * (count / 255.0)) : 0;
				wolf->color.g = wolf->color.g > 0 ? (Uint8)(wolf->color.g * (count / 255.0)) : 0;
				wolf->color.b = wolf->color.b > 0 ? (Uint8)(wolf->color.b * (count / 255.0)) : 0;
				set_pixel_s(wolf, &wolf->color, x, y);
			}
		}
		screen_upd(wolf);
	}
}

void		intro(t_wolf *wolf)
{
	t_texture intro;
	int count = 255;

	load_texture(wolf, &intro, "resource/img/menu/intro-1.jpg");
	cp_tex_to_buff(wolf, &intro);
	intro_anim(wolf, &intro);
	destroy_texture(&intro);
	load_texture(wolf, &intro, "resource/img/menu/intro-2.jpg");
	cp_tex_to_buff(wolf, &intro);
	intro_anim(wolf, &intro);
	destroy_texture(&intro);
	
	SDL_Event event;
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return ;
		}
	}
}

int			main(int ac, char **av)
{
	t_wolf *wolf = malloc(sizeof(t_wolf));
	init(wolf);	

	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_WarpMouseInWindow(wolf->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
intro(wolf);
	// raycast(wolf);

	//close_win(wolf);
	free(wolf);
	//system("leaks test");
	return (0);
}