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

void		intro(t_wolf *wolf)
{
	t_texture intro;
	int count = 255;

	load_texture(wolf, &intro, "resource/img/menu/intro.jpg");
	for (int y = 0; y < intro.sur->h; y++)
	{
		printf("[%d]dfhfgh\n", y);
		for (int x = 0; x < intro.sur->w; x++)
			wolf->buff[(y + 199) * SCREEN_WIDTH + (x + 249)] = intro.pixels[y * intro.sur->w  + x];
	}
	SDL_UpdateTexture(wolf->tex, NULL, wolf->buff, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(wolf->ren);
	SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
	SDL_RenderPresent(wolf->ren);
	SDL_Delay(1000);
	while (count-- > 0)
	{
		SDL_UpdateTexture(wolf->tex, NULL, wolf->buff, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(wolf->ren);
		SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
		SDL_RenderPresent(wolf->ren);
		for (int y = 199; y < 199 + intro.sur->h; y++)
		{
			for (int x = 249; x < 249 + intro.sur->w; x++)
			{
				get_color(&intro, &wolf->color, x - 249, y - 199);
				wolf->color.r = wolf->color.r > 0 ? wolf->color.r * (count / 255.0) : 0;
				wolf->color.g = wolf->color.g > 0 ? wolf->color.g * (count / 255.0) : 0;
				wolf->color.b = wolf->color.b > 0 ? wolf->color.b * (count / 255.0) : 0;
				set_pixel_s(wolf, &wolf->color, x, y);
			}
		}
		// SDL_Delay(5);
	}
}

int			main(int ac, char **av)
{
	t_wolf *wolf = malloc(sizeof(t_wolf));
	init(wolf);	

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(wolf->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
intro(wolf);
	// raycast(wolf);

	close_win(wolf);
	free(wolf);
	// system("leaks test");
	return (0);
}