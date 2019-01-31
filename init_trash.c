/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_trash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 23:09:54 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:26:00 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_chunk(t_wolf *wolf)
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

void	free_chunk(t_wolf *wolf)
{
	int	i;

	i = -1;
	while (++i < 9)
		Mix_FreeChunk(wolf->chunk[i]);
}

void	prepare_chunk(t_wolf *wolf)
{
	int	i;

	i = -1;
	while (++i < 9)
		wolf->chunk[i] = NULL;
}

void	prepare_texture(t_wolf *wolf)
{
	int	i;

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

void	prepare_face(t_texture *face)
{
	int	i;
	int	j;

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
