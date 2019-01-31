/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:50:04 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:26:55 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				free_textures(t_texture *texture, int num)
{
	int			i;

	i = -1;
	while (++i < num)
	{
		if ((texture + i)->sur != NULL)
			destroy_texture(texture + i);
	}
	return (0);
}

int				textures(t_texture *texture, int num, char *p)
{
	int			i;
	char		*path;
	char		*tmp;

	i = -1;
	while (++i < num)
	{
		path = ft_itoa(i);
		tmp = ft_strjoin(path, ".png");
		free(path);
		path = ft_strjoin(p, tmp);
		free(tmp);
		if (!load_texture(texture + i, path))
		{
			free(path);
			return (0);
		}
		free(path);
	}
	return (1);
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
