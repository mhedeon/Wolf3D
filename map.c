/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:39:47 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/20 20:31:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

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

void			loading(t_wolf *wolf, int persent)
{
	t_texture load;
	SDL_Event e;

	if (SDL_PollEvent(&e))
		;
	if (persent <= 10)
		load_texture(&load, "./resource/img/loading/L10.jpg");
	else if (persent > 10 && persent <= 20)
		load_texture(&load, "./resource/img/loading/L20.jpg");
	if (persent > 20 && persent <= 30)
		load_texture(&load, "./resource/img/loading/L30.jpg");
	if (persent > 30 && persent <= 40)
		load_texture(&load, "./resource/img/loading/L40.jpg");
	if (persent > 40 && persent <= 50)
		load_texture(&load, "./resource/img/loading/L50.jpg");
	if (persent > 50 && persent <= 60)
		load_texture(&load, "./resource/img/loading/L60.jpg");
	if (persent > 60 && persent <= 70)
		load_texture(&load, "./resource/img/loading/L70.jpg");
	if (persent > 70 && persent <= 80)
		load_texture(&load, "./resource/img/loading/L80.jpg");
	if (persent > 80 && persent <= 90)
		load_texture(&load, "./resource/img/loading/L90.jpg");
	if (persent >= 90)
		load_texture(&load, "./resource/img/loading/L100.jpg");
	cp_tex_to_buff(wolf, &load);
	screen_upd(wolf);
}

int				map(t_wolf *wolf, char *path)
{
	int			i;
	int			fd;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
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
				return (0);
			}
		}
	}
	close(fd);
	printf("xy check\n");
	return (check_player_xy(wolf));
}

int				check_player_xy(t_wolf *wolf)
{
	static int	yx[2] = { 0, 0 };

	if (wolf->p_x <= 0 || wolf->p_x >= (wolf->m_width - 1) ||
		wolf->p_y <= 0 || wolf->p_y >= (wolf->m_height - 1) ||
		wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].c == 1 ||
		wolf->map[(int)wolf->p_y * wolf->m_width + (int)wolf->p_x].d == 1)
	{
		yx[0] = 0;
		while (++(yx[0]) < (wolf->m_height - 1))
		{
			yx[1] = 0;
			while (++(yx[1]) < (wolf->m_width - 1))
				if (wolf->map[yx[0] * wolf->m_width + yx[1]].c != 1
					&& wolf->map[yx[0] * wolf->m_width + yx[1]].d != 1)
				{
					wolf->p_x = (double)(yx[1]) + 0.5;
					wolf->p_y = (double)(yx[0]) + 0.5;
					return (1);
				}
		}
		return (0);
	}
	wolf->p_x += 0.5;
	wolf->p_y += 0.5;
	return (1);
}
