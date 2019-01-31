/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:39:47 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/31 19:03:25 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		get_wh(t_wolf *wolf, int fd)
{
	char		*line;

	if (!get_next_line(fd, &line))
		return (0);
	if (line[0] != 'r' || (ft_strlen(line) < 4))
	{
		free(line);
		return (0);
	}
	wolf->m_width = ft_atoi(line + 1);
	wolf->m_height = ft_atoi(ft_strchr(line, ' ') == NULL ? "0" :
		ft_strchr(line, ' '));
	if (wolf->m_width < 3 || wolf->m_height < 3)
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

static int		get_xy(t_wolf *wolf, int fd)
{
	char		*line;

	if (!get_next_line(fd, &line))
		return (0);
	if (line[0] != 'c' || (ft_strlen(line) < 4))
	{
		free(line);
		return (0);
	}
	wolf->p_x = ft_atoi(line + 1);
	wolf->p_y = ft_atoi(ft_strchr(line, ' ') == NULL ? "0" :
		ft_strchr(line, ' '));
	free(line);
	return (1);
}

static int		parse_map(t_wolf *wolf, int i, char *line)
{
	int			x;
	char		**map;

	map = ft_strsplit(line, ' ');
	free(line);
	if (matrix_height(map) != wolf->m_width)
	{
		matrix_del(map);
		return (0);
	}
	x = -1;
	while (++x < wolf->m_width)
	{
		if (!check_word(&wolf->map[i * wolf->m_width + x], map[x]))
		{
			matrix_del(map);
			return (0);
		}
	}
	matrix_del(map);
	return (1);
}

void			check_vertical(t_wolf *wolf, int fd)
{
	int			y;

	close(fd);
	y = -1;
	while (++y < wolf->m_height)
	{
		if (wolf->map[y * wolf->m_width + 0].w != 1 ||
			wolf->map[y * wolf->m_width + 0].c != 1)
		{
			wolf->map[y * wolf->m_width + 0].w = 1;
			wolf->map[y * wolf->m_width + 0].c = 1;
		}
		if (wolf->map[y * wolf->m_width + (wolf->m_width - 1)].w != 1 ||
			wolf->map[y * wolf->m_width + (wolf->m_width - 1)].c != 1)
		{
			wolf->map[y * wolf->m_width + (wolf->m_width - 1)].w = 1;
			wolf->map[y * wolf->m_width + (wolf->m_width - 1)].c = 1;
		}
	}
	check_horizontal(wolf);
}

int				map(t_wolf *wolf, char *path)
{
	int			i;
	int			fd;
	char		*line;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (get_error(MAP_FILE));
	if (get_wh(wolf, fd) && get_xy(wolf, fd))
	{
		wolf->map = (t_map *)malloc(sizeof(t_map) *
					wolf->m_width * wolf->m_height);
		i = -1;
		while ((++i < wolf->m_height) && get_next_line(fd, &line))
		{
			loading(wolf, (i / (double)wolf->m_height) * 100);
			if (!parse_map(wolf, i, line))
			{
				close(fd);
				return (get_error(MAP));
			}
		}
		check_vertical(wolf, fd);
		return (check_player_xy(wolf));
	}
	close(fd);
	return (get_error(MAP));
}
