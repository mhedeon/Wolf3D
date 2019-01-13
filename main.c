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
	SDL_Event e;

	count = 256;
	while (--count > 0)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			x = -1;
			while (++x < SCREEN_WIDTH)
			{
				wolf->color.r = (wolf->buff[y * SCREEN_WIDTH + x] >> 16 & 0xFF) > 0 ?
						(wolf->buff[y * SCREEN_WIDTH + x] >> 16 & 0xFF) - 1 : 0;
				wolf->color.g = (wolf->buff[y * SCREEN_WIDTH + x] >> 8 & 0xFF) > 0 ?
						(wolf->buff[y * SCREEN_WIDTH + x] >> 8 & 0xFF) - 1 : 0;
				wolf->color.b = (wolf->buff[y * SCREEN_WIDTH + x] & 0xFF) > 0 ?
						(wolf->buff[y * SCREEN_WIDTH + x] & 0xFF) - 1 : 0;
				set_pixel_s(wolf, &wolf->color, x, y);
			}
		}
		screen_upd(wolf);
		if (SDL_PollEvent(&e))
			if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				break;
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
	
	/*printf("done\n");
	SDL_Event event;
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return ;
		}
	}*/
}

int pause_with_break(Uint32 pause)
{
	static SDL_Event	event;

	while (pause-- > 0)
	{
		if (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				return (1);
		SDL_Delay(1);
	}
	return (0);
}

void menu(t_wolf *wolf)
{
	t_texture menu[2];

	load_texture(wolf, &menu[0], "resource/img/menu/bg-1.jpg");
	printf("1\n");
	load_texture(wolf, &menu[1], "resource/img/menu/bg-2.jpg");
	printf("2\n");
	while (1)
	{
		cp_tex_to_buff(wolf, &menu[0]);
		screen_upd(wolf);
		if (pause_with_break(500))
			break ;
		cp_tex_to_buff(wolf, &menu[1]);
		screen_upd(wolf);
		if (pause_with_break(500))
			break;
	}
}

int			main(int ac, char **av)
{
	t_wolf *wolf = malloc(sizeof(t_wolf));
	init(wolf);	

	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_WarpMouseInWindow(wolf->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
intro(wolf);
menu(wolf);
	// raycast(wolf);

	//close_win(wolf);
	free(wolf);
	//system("leaks test");
	return (0);
}