/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:21:14 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/23 21:31:46 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static int		load_screen(t_texture *load, int persent)
{
	if (persent <= 10)
		return (load_texture(load, "./resource/img/loading/L10.jpg"));
	else if (persent > 10 && persent <= 20)
		return (load_texture(load, "./resource/img/loading/L20.jpg"));
	else if (persent > 20 && persent <= 30)
		return (load_texture(load, "./resource/img/loading/L30.jpg"));
	else if (persent > 30 && persent <= 40)
		return (load_texture(load, "./resource/img/loading/L40.jpg"));
	else if (persent > 40 && persent <= 50)
		return (load_texture(load, "./resource/img/loading/L50.jpg"));
	else if (persent > 50 && persent <= 60)
		return (load_texture(load, "./resource/img/loading/L60.jpg"));
	else if (persent > 60 && persent <= 70)
		return (load_texture(load, "./resource/img/loading/L70.jpg"));
	else if (persent > 70 && persent <= 80)
		return (load_texture(load, "./resource/img/loading/L80.jpg"));
	else if (persent > 80 && persent <= 90)
		return (load_texture(load, "./resource/img/loading/L90.jpg"));
	else if (persent > 90)
		return (load_texture(load, "./resource/img/loading/L100.jpg"));
	return (0);
}

void			loading(t_wolf *wolf, int persent)
{
	t_texture	load;
	SDL_Event	e;

	load.sur = NULL;
	while (SDL_PollEvent(&e))
		;
	if (load_screen(&load, persent))
	{
		cp_tex_to_buff(wolf, &load);
		screen_upd(wolf);
		destroy_texture(&load);
	}
}
