/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:33:41 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 17:25:53 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	get_error_norm(int error)
{
	if (error == FONT_ERR)
		write(1, "Cannot create font\n", 20);
	else if (error == BUFF_ERR)
		write(1, "Cannot allocate memory for buffer\n", 35);
	else if (error == HERO_ERR)
		write(1, "Cannot allocate memory for hero\n", 33);
	else if (error == FACE_ERR)
		write(1, "Cannot load face files\n", 24);
	else if (error == WOLF_ERR)
		write(1, "Cannot allocate memory for game\n", 33);
}

int			get_error(int error)
{
	if (error == MAP_FILE)
		write(1, "Cannot load map file\n", 22);
	else if (error == MAP)
		write(1, "Map error, please go away(((\n", 30);
	else if (error == POSITION_ERR)
		write(1, "Cannot place player on the map\n", 32);
	else if (error == SDL_INIT_ERR)
		write(1, "Cannot load all SDL frameworks\n", 32);
	else if (error == WALL_ERR)
		write(1, "Cannot load wall files\n", 24);
	else if (error == SPRITE_ERR)
		write(1, "Cannot load sprite files\n", 26);
	else if (error == PISTOL_ERR)
		write(1, "Cannot load pistol files\n", 26);
	else if (error == WALL_ERR)
		write(1, "Cannot load knife files\n", 25);
	else if (error == WIN_ERR)
		write(1, "Cannot create window\n", 22);
	else if (error == REN_ERR)
		write(1, "Cannot create renderer\n", 24);
	else if (error == TEX_ERR)
		write(1, "Cannot create texture\n", 23);
	else
		get_error_norm(error);
	return (0);
}
