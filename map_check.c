/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:33:27 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/24 21:44:38 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static int	wall(t_map *map, char *word)
{
	map->w = 1;
	map->s = 0;
	map->c = word[9] - '0';
	map->d = 0;
	map->north = get_number(word[1], word[2]);
	map->south = get_number(word[3], word[4]);
	map->west = get_number(word[5], word[6]);
	map->east = get_number(word[7], word[8]);
	map->sprite = 0;
	map->floor = 0;
	map->ceil = 0;
	if (map->north < 0 || map->south < 0 || map->west < 0 ||
		map->east < 0 || map->north >= WALL_NUM ||
		map->south >= WALL_NUM || map->west >= WALL_NUM ||
		map->east >= WALL_NUM)
		return (0);
	return (1);
}

static int	sprite(t_map *map, char *word)
{
	map->w = 0;
	map->s = 1;
	map->c = word[7] - '0';
	map->d = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	map->east = 0;
	map->sprite = get_number(word[1], word[2]);
	map->floor = get_number(word[3], word[4]);
	map->ceil = get_number(word[5], word[6]);
	if (map->sprite < 0 || map->sprite >= SPRITE_NUM ||
		map->floor < 0 || map->floor >= WALL_NUM ||
		map->ceil < 0 || map->ceil >= WALL_NUM)
		return (0);
	return (1);
}

static int	floor_cell(t_map *map, char *word)
{
	map->w = 0;
	map->s = 0;
	map->c = 0;
	map->d = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	map->east = 0;
	map->sprite = 0;
	map->floor = get_number(word[0], word[1]);
	map->ceil = get_number(word[2], word[3]);
	if (map->floor < 0 || map->floor >= WALL_NUM ||
		map->ceil < 0 || map->ceil >= WALL_NUM)
		return (0);
	return (1);
}

static int	door(t_map *map, char *word)
{
	map->w = 0;
	map->s = 0;
	map->c = 1;
	map->d = 1;
	map->north = get_number(word[1], word[2]);
	map->south = get_number(word[1], word[2]);
	map->west = get_number(word[1], word[2]);
	map->east = get_number(word[1], word[2]);
	map->sprite = 0;
	map->floor = get_number(word[3], word[4]);
	map->ceil = get_number(word[5], word[6]);
	if (map->north < 0 || map->south < 0 || map->west < 0 ||
		map->east < 0 || map->north >= WALL_NUM ||
		map->south >= WALL_NUM || map->west >= WALL_NUM ||
		map->east >= WALL_NUM || map->floor < 0 || map->floor >= WALL_NUM
		|| map->ceil < 0 || map->ceil >= WALL_NUM)
		return (0);
	return (1);
}

int			check_word(t_map *map, char *word)
{
	if (word[0] == 'w' && ft_strlen(word) == 10
		&& check_digit(word))
		return (wall(map, word));
	else if (word[0] == 's' && ft_strlen(word) == 8
		&& check_digit(word))
		return (sprite(map, word));
	else if (word[0] >= '0' && word[0] <= '9' &&
		ft_strlen(word) == 4 && check_digit(word))
		return (floor_cell(map, word));
	else if (word[0] == 'd' && ft_strlen(word) == 7
		&& check_digit(word))
		return (door(map, word));
	else
		return (0);
	return (1);
}
