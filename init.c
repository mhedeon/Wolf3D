/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:19:45 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/24 22:28:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	pre_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	wolf->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	load_texture(&wolf->icon, "./resource/img/menu/icon.png");
	SDL_SetWindowIcon(wolf->win, wolf->icon.sur);
	wolf->ren = SDL_CreateRenderer(wolf->win, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	wolf->tex = SDL_CreateTexture(wolf->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	wolf->keyboard = SDL_GetKeyboardState(NULL);
	wolf->buff = (Uint32 *)malloc(sizeof(Uint32) *
					(SCREEN_HEIGHT * SCREEN_WIDTH));
	wolf->menu.menu[0].sur = NULL;
	wolf->menu.menu[1].sur = NULL;
	wolf->menu.start[0].sur = NULL;
	wolf->menu.start[1].sur = NULL;
	wolf->menu.start[2].sur = NULL;
	wolf->menu.level[0].sur = NULL;
	wolf->menu.level[1].sur = NULL;
	wolf->menu.cursor.sur = NULL;
	SDL_ShowCursor(SDL_DISABLE);
	if (!textures(wolf->wall, WALL_NUM, "./resource/img/walls/"))
		return (free_textures(wolf->wall, WALL_NUM, NULL, NULL));
printf("walls done\n");
	if (!textures(wolf->sprite, SPRITE_NUM, "./resource/img/sprites/"))
		return (free_textures(wolf->sprite, SPRITE_NUM, NULL, NULL));
printf("sprites done\n");
	if (!textures(wolf->knife, WEAPON_NUM, "./resource/img/knife/"))
		return (free_textures(wolf->knife, WEAPON_NUM, NULL, NULL));
printf("knife done\n");
	if (!textures(wolf->pistol, WEAPON_NUM, "./resource/img/pistol/"))
		return (free_textures(wolf->pistol, WEAPON_NUM, NULL, NULL));
printf("pistol done\n");
	return (1);
}

void	free_garbage_1(t_wolf *wolf)
{
	destroy_texture(&wolf->icon);
	SDL_RenderClear(wolf->ren);
	SDL_DestroyTexture(wolf->tex);
	SDL_DestroyRenderer(wolf->ren);
	SDL_DestroyWindow(wolf->win);
	SDL_ShowCursor(SDL_ENABLE);
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
	free_textures(wolf->wall, WALL_NUM, NULL, NULL);
	free_textures(wolf->sprite, SPRITE_NUM, NULL, NULL);
	free_textures(wolf->knife, WEAPON_NUM, NULL, NULL);
	free_textures(wolf->pistol, WEAPON_NUM, NULL, NULL);
	free(wolf->buff);
	free(wolf);
}

int	free_garbage_2(t_wolf *wolf)
{
	free(wolf->hero);
	if (wolf->map != NULL)
		free(wolf->map);
	wolf->map = NULL;
	return (0);
}

void	post_init(t_wolf *wolf)
{
	wolf->map = NULL;
	wolf->hero = (t_stats *)malloc(sizeof(t_stats));
	wolf->hero->healh = 50;
	wolf->hero->bullet = 8;
	wolf->hero->score = 0;
	wolf->door.opened = 0;
	wolf->p_x = 0;
	wolf->p_y = 0;
	wolf->dir_x = 1;
	wolf->dir_y = 0;
	wolf->plane_x = 0;
	wolf->plane_y = 0.66;
	wolf->old_mouse_x = SCREEN_WIDTH / 2;
	wolf->start_frame = 0;
	wolf->end_frame = 0;
	wolf->frame = 0;
	wolf->ms = 0;
	wolf->rs = 0;
	wolf->fps = 60;
	wolf->sens = 1.0;
	wolf->weapon = 1;
	wolf->shot = 0;
	SDL_WarpMouseInWindow(wolf->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
