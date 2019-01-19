/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:19:45 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/19 23:18:01 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void pre_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	wolf->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);// | SDL_WINDOW_FULLSCREEN_DESKTOP);
	wolf->ren = SDL_CreateRenderer(wolf->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	wolf->tex = SDL_CreateTexture(wolf->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	wolf->keyboard = SDL_GetKeyboardState(NULL);
	wolf->buff = (Uint32 *)malloc(sizeof(Uint32) * (SCREEN_HEIGHT * SCREEN_WIDTH));
	wolf->menu.menu[0].sur = NULL;
	wolf->menu.menu[1].sur = NULL;
	wolf->menu.start[0].sur = NULL;
	wolf->menu.start[1].sur = NULL;
	wolf->menu.start[2].sur = NULL;
	wolf->menu.level[0].sur = NULL;
	wolf->menu.level[1].sur = NULL;
	wolf->menu.cursor.sur = NULL;
}

void free_garbage_1(t_wolf *wolf)
{
	SDL_RenderClear(wolf->ren);
	SDL_DestroyTexture(wolf->tex);
	SDL_DestroyRenderer(wolf->ren);
	SDL_DestroyWindow(wolf->win);
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
	free(wolf->buff);
	free(wolf);
}



void post_init(t_wolf *wolf)
{
	wolf->hero = (t_stats *)malloc(sizeof(t_stats));
	wolf->hero->healh = 50;
	wolf->hero->bullet = 8;
	wolf->hero->score = 0;
	wolf->door.opened = 0;
	textures(wolf);
	sprites(wolf);
	wolf->p_x = 31;
	wolf->p_y = 50.5;
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
	wolf->fps = 0;
}

int textures(t_wolf *wolf)
{
	int i;
	int fd;
	char *line;
	char *path;

	fd = open("./resource/img/walls/walls", O_RDONLY);
	i = -1;
	while (++i < WALL_NUM && get_next_line(fd, &line))
	{
		path = ft_strjoin("./resource/img/walls/", line);
		load_texture(&wolf->wall[i], path);
		free(path);
		free(line);
	}
	close(fd);
	return (1);
}

int free_sprites(t_wolf *wolf, int i, char *path, char *line)
{
	if (path != NULL)
		free(path);
	if (line != NULL)
		free(line);
	while (i-- >= 0)
	{
		if (wolf->sprite[i].sur != NULL)
			destroy_texture(&wolf->sprite[i]);
		i--;
	}
	return (0);
}

int sprites(t_wolf *wolf)
{
	int i;
	int fd;
	char *line;
	char *path;

	fd = open("./resource/img/sprites/sprites", O_RDONLY);
	if (fd != -1)
	{
		i = -1;
		while (++i < SPRITE_NUM && get_next_line(fd, &line))
		{
			path = ft_strjoin("./resource/img/sprites/", line);
			if (!load_texture(&wolf->sprite[i], path))
			{
				close(fd);
				return (free_sprites(wolf, i, path, line));
				// return (0);
			}
			free(path);
			free(line);
		}
		close(fd);
		return (1);
	}
	return (0);
}

int load_texture(t_texture *tex, char *path)
{
	SDL_Surface *tmp;

	tex->sur = IMG_Load(path);
	if (tex->sur == NULL)
		return (0);
	tmp = SDL_ConvertSurfaceFormat(tex->sur, SDL_PIXELFORMAT_ARGB8888, 0);
	if (tmp == NULL)
	{
		destroy_texture(tex);
		return (0);
	}
	SDL_FreeSurface(tex->sur);
	tex->sur = tmp;
	SDL_LockSurface(tex->sur);
	tex->pixels = tex->sur->pixels;
	return (1);
}

void destroy_texture(t_texture *tex)
{
	SDL_UnlockSurface(tex->sur);
	SDL_FreeSurface(tex->sur);
	tex->sur = NULL;
	tex->pixels = NULL;
}

void	close_win(t_wolf *wolf)
{
	int	i;

	i = -1;
	while (++i < WALL_NUM)
		destroy_texture(&wolf->wall[i]);
	i= -1;
	while (++i < SPRITE_NUM)
		destroy_texture(&wolf->sprite[i]);
	SDL_RenderClear(wolf->ren);
	SDL_DestroyTexture(wolf->tex);
	SDL_DestroyRenderer(wolf->ren);
	SDL_DestroyWindow(wolf->win);
	IMG_Quit();
	SDL_Quit();
	free(wolf->buff);
	free(wolf->hero);
	// free(wolf->map);
}