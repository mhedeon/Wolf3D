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

int pause_with_break(t_wolf *wolf, Uint32 pause)
{
	static SDL_Event	event;

	while (pause-- > 0)
	{
		if (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
				event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				return (1);
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

int			main(int ac, char **av)
{
	t_wolf *wolf;
	int lvl;
	
	wolf = malloc(sizeof(t_wolf));
	pre_init(wolf);
	intro(wolf);
	while (1)
	{
		if (init_menu_screen(&wolf->menu) &&
			init_menu_sound(&wolf->menu))
		{
			lvl = menu(wolf, &wolf->menu);
			free_menu_screen(&wolf->menu);
			free_menu_sound(&wolf->menu);
		}
		else
			break ;
		if (lvl == 0)
			break ;
	}


	//system("leaks test");
	return (0);
}