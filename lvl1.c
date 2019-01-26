/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:46:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/26 22:33:24 by mhedeon          ###   ########.fr       */
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
			Mix_PlayChannel(-1, wolf->left_click, 0);
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
	if (wolf->shot && wolf->weapon == 1)
		shoot(wolf, wolf->knife, SDL_GetTicks(),
				"./resource/sounds/chunk/Knife.wav");
	else if (wolf->shot && wolf->weapon == 2)
		shoot(wolf, wolf->pistol, SDL_GetTicks(),
				"./resource/sounds/chunk/Pistol.wav");
	else if (wolf->weapon == 1)
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

void show_health(t_wolf *wolf)
{
	SDL_Rect r;
	char *tmp;
	char *tmp2;
	SDL_Surface *sur;
	SDL_Texture *message;

	tmp2 = ft_itoa(wolf->hero->health);
	tmp = ft_strjoin("+", tmp2);
	sur = TTF_RenderText_Solid(wolf->font, tmp, (SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = r.x / 10;
	r.h = r.x / 10;
	SDL_RenderCopy(wolf->ren, message, NULL, &(SDL_Rect) {r.x / 2 - 2.5 * r.w, r.y - r.h, r.w, r.h});
	free(tmp);
	free(tmp2);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

void show_bullet(t_wolf *wolf)
{
	SDL_Rect r;
	char *tmp;
	char *tmp2;
	SDL_Surface *sur;
	SDL_Texture *message;

	tmp2 = ft_itoa(wolf->hero->bullet);
	tmp = ft_strjoin("\%", tmp2);
	sur = TTF_RenderText_Solid(wolf->font, tmp, (SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = 2 * r.x / 10;
	r.h = r.x / 10;
	SDL_RenderCopy(wolf->ren, message, NULL, &(SDL_Rect) {r.x / 2 + 0.75 * r.w, r.y - r.h * 0.80, r.w, r.h});
	free(tmp);
	free(tmp2);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

void show_score(t_wolf *wolf)
{
	SDL_Rect r;
	char *tmp;
	SDL_Surface *sur;
	SDL_Texture *message;

	tmp = ft_itoa(wolf->hero->score);
	sur = TTF_RenderText_Solid(wolf->font, tmp, (SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = r.x / 10;
	r.h = r.x / 10;
	SDL_RenderCopy(wolf->ren, message, NULL, &(SDL_Rect) {50, r.y - r.h, r.w, r.h});
	free(tmp);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

void draw_face(t_wolf *wolf, t_texture *face, int time)
{
	static int ticks = 0;

	ticks = time - ticks >= 8000 ? SDL_GetTicks() : ticks;
	if ((time - ticks) < 1000)
		draw_cursor(wolf, face + 1, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 1)->sur->w,
		SCREEN_HEIGHT - (face + 1)->sur->h, (face + 1)->sur->w, (face + 1)->sur->h });
	else if ((time - ticks) < 2000)
		draw_cursor(wolf, face + 2, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 2)->sur->w,
		SCREEN_HEIGHT - (face + 2)->sur->h, (face + 2)->sur->w, (face + 2)->sur->h });
	else if ((time - ticks) < 3000)
		draw_cursor(wolf, face + 3, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 3)->sur->w,
		SCREEN_HEIGHT - (face + 3)->sur->h, (face + 3)->sur->w, (face + 3)->sur->h });
	else if ((time - ticks) < 4000)
		draw_cursor(wolf, face + 4, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 4)->sur->w,
		SCREEN_HEIGHT - (face + 4)->sur->h, (face + 4)->sur->w, (face + 4)->sur->h });
	else if ((time - ticks) < 5000)
		draw_cursor(wolf, face + 5, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 5)->sur->w,
		SCREEN_HEIGHT - (face + 5)->sur->h, (face + 5)->sur->w, (face + 5)->sur->h });
	else if ((time - ticks) < 6000)
		draw_cursor(wolf, face + 6, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 6)->sur->w,
		SCREEN_HEIGHT - (face + 6)->sur->h, (face + 6)->sur->w, (face + 6)->sur->h });
	else if ((time - ticks) < 7000)
		draw_cursor(wolf, face + 7, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 7)->sur->w,
		SCREEN_HEIGHT - (face + 7)->sur->h, (face + 7)->sur->w, (face + 7)->sur->h });
	else if ((time - ticks) < 8000)
		draw_cursor(wolf, face + 8, &(SDL_Rect) { SCREEN_WIDTH / 2 - 2 * (face + 8)->sur->w,
		SCREEN_HEIGHT - (face + 8)->sur->h, (face + 8)->sur->w, (face + 8)->sur->h });
}

void face(t_wolf *wolf)
{
	if (wolf->hero->health <= 15)
		draw_face(wolf, wolf->face + 60, SDL_GetTicks());
	else if (wolf->hero->health > 15 && wolf->hero->health <= 30)
		draw_face(wolf, wolf->face + 50, SDL_GetTicks());
	else if (wolf->hero->health > 30 && wolf->hero->health <= 45)
		draw_face(wolf, wolf->face + 40, SDL_GetTicks());
	else if (wolf->hero->health > 45 && wolf->hero->health <= 60)
		draw_face(wolf, wolf->face + 30, SDL_GetTicks());
	else if (wolf->hero->health > 60 && wolf->hero->health <= 75)
		draw_face(wolf, wolf->face + 20, SDL_GetTicks());
	else if (wolf->hero->health > 75 && wolf->hero->health <= 90)
		draw_face(wolf, wolf->face + 10, SDL_GetTicks());
	else if (wolf->hero->health > 90)
		draw_face(wolf, wolf->face + 0, SDL_GetTicks());
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
		weapon(wolf);
		face(wolf);
		fps(wolf);
		wolf->ms = 1 / 30.0 * 5.0;
		wolf->start_frame = wolf->end_frame;
		SDL_UpdateTexture(wolf->tex, NULL, wolf->buff, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(wolf->ren);
		SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
		show_health(wolf);
		show_bullet(wolf);
		show_score(wolf);
		SDL_RenderPresent(wolf->ren);
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
