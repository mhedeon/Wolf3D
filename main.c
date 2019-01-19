/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/19 23:18:12 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"



int			main(int ac, char **av)
{
	t_wolf *wolf;
	int lvl;
	
	wolf = malloc(sizeof(t_wolf));
	pre_init(wolf);
	intro(wolf);
	// sprites(wolf);
	// free_sprites(wolf, SPRITE_NUM, NULL, NULL);
	while (1)
	{
		lvl = start_menu(wolf, &wolf->menu);
		if (lvl < 1)
			break ;
	}

	free_garbage_1(wolf);
	system("leaks Wolf3D");
	return (0);
}