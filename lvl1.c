/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:46:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/24 23:06:53 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void shooot(t_wolf *wolf, t_texture *weapon, int start, int time)
{
	if ((time - start) < 75)
		draw_cursor(wolf, weapon + 1, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					1)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 1)->sur->h,
					(weapon + 1)->sur->w, (weapon + 1)->sur->h });
	else if ((time - start) < 150)
		draw_cursor(wolf, weapon + 2, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					2)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 2)->sur->h,
					(weapon + 2)->sur->w, (weapon + 2)->sur->h });
	else if ((time - start) < 225)
		draw_cursor(wolf, weapon + 3, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					3)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 3)->sur->h,
					(weapon + 3)->sur->w, (weapon + 3)->sur->h });
	else if ((time - start) < 300)
		draw_cursor(wolf, weapon + 4, &(SDL_Rect){ (SCREEN_WIDTH - (weapon +
					4)->sur->w) / 2, SCREEN_HEIGHT - (weapon + 4)->sur->h,
					(weapon + 4)->sur->w, (weapon + 4)->sur->h });
}

void shoot(t_wolf *wolf, t_texture *weapon, int time, char *path)
{
	static int start = 0;

	if (start == 0 && wolf->shot)
	{
		wolf->left_click = Mix_LoadWAV(path);
		if (wolf->left_click != NULL)
			Mix_PlayChannel(1, wolf->left_click, 0);
		start = SDL_GetTicks();
	}
	else
	{
		shooot(wolf, weapon, start, time);
		if ((time - start) >= 300)
		{
			wolf->shot = 0;
			start = 0;
			if (wolf->left_click != NULL)
				Mix_FreeChunk(wolf->left_click);
		}
	}
}

void weapon(t_wolf *wolf)
{
	if (wolf->weapon == 1)
		draw_cursor(wolf, &wolf->knife[0], &(SDL_Rect){ SCREEN_WIDTH / 2 -
					wolf->knife[0].sur->w / 2, SCREEN_HEIGHT - wolf->knife
					[0].sur->h, wolf->knife[0].sur->w, wolf->knife[0].sur->h });
	else if (wolf->weapon == 2)
		draw_cursor(wolf, &wolf->pistol[0], &(SDL_Rect){ SCREEN_WIDTH / 2 -
					wolf->pistol[0].sur->w / 2, SCREEN_HEIGHT - wolf->pistol
				[0].sur->h, wolf->pistol[0].sur->w, wolf->pistol[0].sur->h });
}

static int prepare_lvl(t_wolf *wolf)
{
	wolf->lvl_music = Mix_LoadMUS("./resource/sounds/music/lvl1.mid");
	if (wolf->lvl_music != NULL)
		Mix_PlayMusic(wolf->lvl_music, -1);
	return (1);
}

static void clear_lvl(t_wolf *wolf)
{
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	if (wolf->lvl_music != NULL)
		Mix_FreeMusic(wolf->lvl_music);
}

static void game(t_wolf *wolf)
{
	while (event(wolf))
	{
		if (wolf->door.opened)
			close_door(wolf);
		check_item(wolf);
		cast_loop(wolf);
		draw_x(wolf);
		if (wolf->shot && wolf->weapon == 1)
			shoot(wolf, wolf->knife, SDL_GetTicks(),
					"./resource/sounds/chunk/Knife.wav");
		else if (wolf->shot && wolf->weapon == 2)
			shoot(wolf, wolf->pistol, SDL_GetTicks(),
					"./resource/sounds/chunk/Pistol.wav");
		else
			weapon(wolf);
		// screen_upd(wolf);
		fps(wolf);
		wolf->ms = 1 / 30.0 * 5.0;
		wolf->start_frame = wolf->end_frame;
		// screen_upd(wolf);


		TTF_Font *font = TTF_OpenFont("wolfenstein.ttf", 24);
		SDL_Surface *sm = TTF_RenderText_Solid(font, ft_itoa(wolf->hero->healh), (SDL_Color) {255, 255, 255, 255});
		SDL_Texture *message = SDL_CreateTextureFromSurface(wolf->ren, sm);
		SDL_RenderClear(wolf->ren);
		SDL_UpdateTexture(wolf->tex, NULL, wolf->buff, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
		int x, y;
		SDL_GetWindowSize(wolf->win, &x, &y);
		SDL_RenderCopy(wolf->ren, message, NULL, &(SDL_Rect) {50, y - 100, 100, 100});
		SDL_RenderPresent(wolf->ren);
	
		SDL_FreeSurface(sm);
		SDL_DestroyTexture(message);
		TTF_CloseFont(font);



		clear_buffer(wolf);
	}
}

void start_lvl_1(t_wolf *wolf)
{
	wolf->lvl_music = NULL;
	if (map(wolf, "resource/maps/01lvl.wolfmap") && prepare_lvl(wolf))
	{
		game(wolf);
	}
	clear_lvl(wolf);
}
