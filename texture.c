/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:50:04 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/21 18:30:17 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int				free_textures(t_texture *texture, int i, char *path, char *line)
{
	if (path != NULL)
		free(path);
	if (line != NULL)
		free(line);
	while (--i >= 0)
	{
		if ((texture + i)->sur != NULL)
			destroy_texture(texture + i);
	}
	return (0);
}

int				textures(t_texture *texture, int num, char *p)
{
	int			i;
	int			fd;
	char		*line;
	char		*path;

	fd = open((num == WALL_NUM ? "./resource/img/walls/walls" :
		"./resource/img/sprites/sprites"), O_RDONLY);
	if (fd != -1)
	{
		i = -1;
		while (++i < num && get_next_line(fd, &line))
		{
			path = ft_strjoin(p, line);
			if (!load_texture(texture + i, path))
			{
				close(fd);
				return (free_textures(texture, i, path, line));
			}
			free(path);
			free(line);
		}
		close(fd);
		return (i == num ? 1 : 0);
	}
	return (0);
}

int				load_texture(t_texture *tex, char *path)
{
	SDL_Surface	*tmp;

	tex->sur = NULL;
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

void			destroy_texture(t_texture *tex)
{
	if (tex->sur != NULL)
	{
		SDL_UnlockSurface(tex->sur);
		SDL_FreeSurface(tex->sur);
	}
	tex->sur = NULL;
	tex->pixels = NULL;
}
