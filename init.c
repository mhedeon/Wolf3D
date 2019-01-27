/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:19:45 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/27 22:17:34 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void load_chunk(t_wolf *wolf)
{
	wolf->chunk[0] = Mix_LoadWAV("resource/sounds/chunk/Ammo.wav");
	wolf->chunk[1] = Mix_LoadWAV("resource/sounds/chunk/Pickup.wav");
	wolf->chunk[2] = Mix_LoadWAV("resource/sounds/chunk/Health.wav");
	wolf->chunk[3] = Mix_LoadWAV("resource/sounds/chunk/Door.wav");
	wolf->chunk[4] = Mix_LoadWAV("resource/sounds/chunk/Secret Entrance.wav");
	wolf->chunk[5] = Mix_LoadWAV("resource/sounds/chunk/Enemy Pain.wav");
	wolf->chunk[6] = Mix_LoadWAV("resource/sounds/chunk/Death 1.wav");
	wolf->chunk[7] = Mix_LoadWAV("resource/sounds/chunk/Pistol.wav");
	wolf->chunk[8] = Mix_LoadWAV("resource/sounds/chunk/Knife.wav");
}

void free_chunk(t_wolf *wolf)
{
	Mix_FreeChunk(wolf->chunk[0]);
	Mix_FreeChunk(wolf->chunk[1]);
	Mix_FreeChunk(wolf->chunk[2]);
	Mix_FreeChunk(wolf->chunk[3]);
	Mix_FreeChunk(wolf->chunk[4]);
	Mix_FreeChunk(wolf->chunk[5]);
	Mix_FreeChunk(wolf->chunk[6]);
	Mix_FreeChunk(wolf->chunk[7]);
	Mix_FreeChunk(wolf->chunk[8]);
}

void prepare_texture(t_wolf *wolf)
{
	int i;

	i = -1;
	while (++i < WALL_NUM)
		wolf->wall[i].sur = NULL;
	i = -1;
	while (++i < SPRITE_NUM)
		wolf->sprite[i].sur = NULL;
	i = -1;
	while (++i < WEAPON_NUM)
		wolf->knife[i].sur = NULL;
	i = -1;
	while (++i < WEAPON_NUM)
		wolf->pistol[i].sur = NULL;
}

int	pre_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
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
	wolf->font = TTF_OpenFont("resource/ttf/wolfenstein.ttf", 25);
	prepare_face(wolf->face);
	load_face(wolf->face);
	prepare_texture(wolf);
	if (!textures(wolf->wall, WALL_NUM, "./resource/img/walls/"))
		return (0);
	if (!textures(wolf->sprite, SPRITE_NUM, "./resource/img/sprites/"))
		return (0);
	if (!textures(wolf->pistol, WEAPON_NUM, "./resource/img/pistol/"))
		return (0);
	if (!textures(wolf->knife, WEAPON_NUM, "./resource/img/knife/"))
		return (0);
	load_chunk(wolf);
	return (1);
}

void	free_garbage_1(t_wolf *wolf)
{
	free_chunk(wolf);
	SDL_RenderClear(wolf->ren);
	SDL_DestroyTexture(wolf->tex);
	SDL_DestroyRenderer(wolf->ren);
	SDL_DestroyWindow(wolf->win);
	SDL_ShowCursor(SDL_ENABLE);
	TTF_CloseFont(wolf->font);
	destroy_texture(&wolf->icon);
	free_face(wolf->face);
	free_textures(wolf->wall, WALL_NUM);
	free_textures(wolf->sprite, SPRITE_NUM);
	free_textures(wolf->pistol, WEAPON_NUM);
	free_textures(wolf->knife, WEAPON_NUM);
	free(wolf->buff);
	free(wolf);
	IMG_Quit();
	Mix_CloseAudio();
	TTF_Quit();
	// SDL_Quit();
}

int	free_garbage_2(t_wolf *wolf)
{
	free(wolf->hero);
	// if (wolf->map != NULL)
	// 	free(wolf->map);
	// wolf->map = NULL;
	return (0);
}

void	post_init(t_wolf *wolf)
{
	wolf->map = NULL;
	wolf->hero = (t_stats *)malloc(sizeof(t_stats));
	wolf->hero->health = 60;
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

int load_face(t_texture *face)
{
	int i;
	int j;
	char *tmp[2];

	j = 10;
	while (j <= 70)
	{
		i = 0;
		while (++i <= 8)
		{
			tmp[0] = ft_itoa(j + i);
			tmp[1] = ft_strjoin(tmp[0], ".png");
			free(tmp[0]);
			tmp[0] = ft_strjoin("resource/img/face/", tmp[1]);
			free(tmp[1]);
			if (!load_texture(&face[j - 10 + i], tmp[0]))
			{
				free(tmp[0]);
				return (0);
			}
			free(tmp[0]);
		}
		j += 10;
	}
	return (1);
}

int free_face(t_texture *face)
{
	int i;
	int j;

	j = 10;
	while (j <= 70)
	{
		i = 0;
		while (++i <= 8)
		{
			if (face[j - 10 + i].sur != NULL)
				destroy_texture(&face[j - 10 + i]);
		}
		j += 10;
	}
	return (0);
}

void prepare_face(t_texture *face)
{
	int i;
	int j;

	j = 10;
	while (j <= 70)
	{
		i = 0;
		while (++i <= 8)
		{
			face[j - 10 + i].sur = NULL;
		}
		j += 10;
	}
}
