/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:24 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/20 20:32:37 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"



int			main(void)
{
	t_wolf *wolf;
	int lvl;
	
	wolf = malloc(sizeof(t_wolf));
	pre_init(wolf);
	// intro(wolf);
	// while (1)
	// {
	// 	lvl = start_menu(wolf, &wolf->menu);
	// 	if (lvl < 1)
	// 		break ;
	// }
	post_init(wolf);

	if (map(wolf, "resource/maps/map1.wolfmap"))
		printf("x: %f\ny: %f\n", wolf->p_x, wolf->p_y);
	else
		printf("map error\n");

	free_garbage_2(wolf);
	free_garbage_1(wolf);
	// system("leaks Wolf3D");
	return (0);
}