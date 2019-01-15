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

void		cp_tex_to_buff(t_wolf *wolf, t_texture *tex);
void		intro_anim(t_wolf *wolf, t_texture *intro);
void		intro(t_wolf *wolf);
int pause_with_break(t_wolf *wolf, Uint32 pause);
void ng_anim(t_wolf *wolf);
int init_menu(t_menu *menu);
int free_menu(t_menu *menu);

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

	load_texture(&intro, "resource/img/menu/intro-1.jpg");
	cp_tex_to_buff(wolf, &intro);
	intro_anim(wolf, &intro);
	destroy_texture(&intro);
	load_texture(&intro, "resource/img/menu/intro-2.jpg");
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

int pause_with_break(t_wolf *wolf, Uint32 pause)
{
	static SDL_Event	event;

	while (pause-- > 0)
	{
		if (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				return (1);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_N)
			{
				ng_anim(wolf);
				return (1);
			}
		SDL_Delay(1);
	}
	return (0);
}

void ng_anim(t_wolf *wolf)
{
	t_texture ng[3];

	load_texture(&ng[0], "resource/img/menu/start-1.jpg");
	load_texture(&ng[1], "resource/img/menu/start-2.jpg");
	load_texture( &ng[2], "resource/img/menu/start-3.jpg");
	cp_tex_to_buff(wolf, &ng[0]);
	screen_upd(wolf);
	pause_with_break(wolf, 200);

	cp_tex_to_buff(wolf, &ng[1]);
	screen_upd(wolf);
	screen_upd(wolf);
	pause_with_break(wolf, 200);

	cp_tex_to_buff(wolf, &ng[2]);
	screen_upd(wolf);
	screen_upd(wolf);
	pause_with_break(wolf, 5000);
}

void menu(t_wolf *wolf)
{
	t_texture menu[2];

	load_texture(&menu[0], "resource/img/menu/menu-1.jpg");
	load_texture(&menu[1], "resource/img/menu/menu-2.jpg");
	while (1)
	{
		cp_tex_to_buff(wolf, &menu[0]);
		screen_upd(wolf);
		if (pause_with_break(wolf, 500))
			break ;
		cp_tex_to_buff(wolf, &menu[1]);
		screen_upd(wolf);
		if (pause_with_break(wolf, 500))
			break;
	}
}

int free_menu(t_menu *menu)
{
	if (menu->menu[0].sur != NULL)
		destroy_texture(&menu->menu[0]);
	if (menu->menu[1].sur != NULL)
		destroy_texture(&menu->menu[1]);
	if (menu->level[0].sur != NULL)
		destroy_texture(&menu->level[0]);
	if (menu->level[1].sur != NULL)
		destroy_texture(&menu->level[1]);
	if (menu->start[0].sur != NULL)
		destroy_texture(&menu->start[0]);
	if (menu->start[1].sur != NULL)
		destroy_texture(&menu->start[1]);
	if (menu->start[2].sur != NULL)
		destroy_texture(&menu->start[2]);
	if (menu->cursor.sur != NULL)
		destroy_texture(&menu->cursor);
	return (0);
}

int init_menu(t_menu *menu)
{
	if (!load_texture(&menu->menu[0], "resource/img/menu/menu-1.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->menu[1], "resource/img/menu/menu-2.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->level[0], "resource/img/menu/level-1.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->level[1], "resource/img/menu/level-2.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->start[0], "resource/img/menu/start-1.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->start[1], "resource/img/menu/start-2.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->start[2], "resource/img/menu/start-3.jpg"))
		return (free_menu(menu));
	if (!load_texture(&menu->cursor, "resource/img/menu/cursor.jpg"))
		return (free_menu(menu));
	return (1);
}

int			main(int ac, char **av)
{
	t_wolf *wolf = malloc(sizeof(t_wolf));
	pre_init(wolf);	

intro(wolf);
menu(wolf);



	//system("leaks test");
	return (0);
}