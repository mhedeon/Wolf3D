/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:19:45 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/29 22:03:35 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static int	pre_init_2(t_wolf *wolf)
{
	wolf->hero = (t_stats *)malloc(sizeof(t_stats));
	if (wolf->hero == NULL)
		return (get_error(HERO_ERR));
	wolf->hero->health = 60;
	wolf->hero->bullet = 8;
	wolf->hero->score = 0;
	SDL_ShowCursor(SDL_DISABLE);
	load_texture(&wolf->icon, "./resource/img/menu/icon.png");
	SDL_SetWindowIcon(wolf->win, wolf->icon.sur);
	if (!textures(wolf->wall, WALL_NUM, "./resource/img/walls/"))
		return (get_error(WALL_ERR));
	if (!textures(wolf->sprite, SPRITE_NUM, "./resource/img/sprites/"))
		return (get_error(SPRITE_ERR));
	if (!textures(wolf->pistol, WEAPON_NUM, "./resource/img/pistol/"))
		return (get_error(PISTOL_ERR));
	if (!textures(wolf->knife, WEAPON_NUM, "./resource/img/knife/"))
		return (get_error(KNIFE_ERR));
	if (!load_face(wolf->face))
		return (get_error(FACE_ERR));
	load_chunk(wolf);
	return (1);
}

static int	pre_init_1(t_wolf *wolf)
{
	wolf->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	if (wolf->win == NULL)
		return (get_error(WIN_ERR));
	wolf->ren = SDL_CreateRenderer(wolf->win, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (wolf->ren == NULL)
		return (get_error(REN_ERR));
	wolf->tex = SDL_CreateTexture(wolf->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (wolf->tex == NULL)
		return (get_error(TEX_ERR));
	wolf->font = TTF_OpenFont("resource/ttf/wolfenstein.ttf", 25);
	if (wolf->font == NULL)
		return (get_error(FONT_ERR));
	wolf->keyboard = SDL_GetKeyboardState(NULL);
	wolf->buff = (Uint32 *)malloc(sizeof(Uint32) *
					(SCREEN_HEIGHT * SCREEN_WIDTH));
	if (wolf->buff == NULL)
		return (get_error(BUFF_ERR));
	return (pre_init_2(wolf));
}

int			pre_init(t_wolf *wolf)
{
	wolf->menu.menu[0].sur = NULL;
	wolf->menu.menu[1].sur = NULL;
	wolf->menu.start[0].sur = NULL;
	wolf->menu.start[1].sur = NULL;
	wolf->menu.start[2].sur = NULL;
	wolf->menu.level[0].sur = NULL;
	wolf->menu.level[1].sur = NULL;
	wolf->menu.cursor.sur = NULL;
	prepare_face(wolf->face);
	prepare_texture(wolf);
	prepare_chunk(wolf);
	wolf->win = NULL;
	wolf->ren = NULL;
	wolf->tex = NULL;
	wolf->font = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() == -1 ||
		!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ||
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		return (get_error(SDL_INIT_ERR));
	return (pre_init_1(wolf));
}

void		free_garbage_1(t_wolf *wolf)
{
	free_chunk(wolf);
	if (wolf->ren)
		SDL_RenderClear(wolf->ren);
	if (wolf->tex)
		SDL_DestroyTexture(wolf->tex);
	if (wolf->ren)
		SDL_DestroyRenderer(wolf->ren);
	if (wolf->win)
		SDL_DestroyWindow(wolf->win);
	TTF_CloseFont(wolf->font);
	destroy_texture(&wolf->icon);
	free_face(wolf->face);
	free_textures(wolf->wall, WALL_NUM);
	free_textures(wolf->sprite, SPRITE_NUM);
	free_textures(wolf->pistol, WEAPON_NUM);
	free_textures(wolf->knife, WEAPON_NUM);
	free(wolf->hero);
	free(wolf->buff);
	free(wolf);
	IMG_Quit();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

void		post_init(t_wolf *wolf)
{
	wolf->map = NULL;
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
	wolf->fps = 30;
	wolf->sens = 1.0;
	wolf->weapon = 1;
	wolf->shot = 0;
	SDL_WarpMouseInWindow(wolf->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
