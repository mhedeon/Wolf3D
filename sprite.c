/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:29:40 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/21 21:21:46 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void draw_sprite(t_wolf *wolf, int x)
{
	double spriteX = wolf->m_x + 0.5 - wolf->p_x;
	double spriteY = wolf->m_y + 0.5 - wolf->p_y;
	double inv_det = 1.0 / (wolf->plane_x * wolf->dir_y - wolf->plane_y * wolf->dir_x);
	double transX = inv_det * (wolf->dir_y * spriteX - wolf->dir_x * spriteY);
	double transY = inv_det * (-wolf->plane_y * spriteX + wolf->plane_x * spriteY);
	int ssx = (int)((SCREEN_WIDTH / 2) * (1 + transX / transY));
	int spriteH = abs((int)(SCREEN_HEIGHT / transY));
	wolf->sp_start = -spriteH / 2 + SCREEN_HEIGHT / 2;
	wolf->sp_end = spriteH / 2 + SCREEN_HEIGHT / 2;
	if (wolf->sp_end >= SCREEN_HEIGHT)
		wolf->sp_end = SCREEN_HEIGHT - 1;
	if (wolf->sp_start <= 0)
		wolf->sp_start = 0;
	int tx = (int)(256 * (x - (-abs( (int) (SCREEN_HEIGHT / (transY))) / 2 + ssx)) * SPRITE_WIDTH / abs( (int) (SCREEN_HEIGHT / (transY)))) / 256;
	int y = wolf->sp_start - 1;
	// printf("start: %d | end: %d\n", start, end);
	while (++y < wolf->sp_end)
	{
		int ty = (((y * 2 - SCREEN_HEIGHT + spriteH) * SPRITE_WIDTH) / spriteH) / 2;
		// if (!(((Uint8)(wolf->wall[8].pixels[y * 64 + x] >> 16 & 0xFF) > 0) &&
		// 	((Uint8)(wolf->wall[8].pixels[y * 64 + x] >> 8 & 0xFF) > 0) &&
		// 	((Uint8)(wolf->wall[8].pixels[y * 64 + x] & 0xFF) > 0)))
		// printf("tx: %d | ty: %d\n", tx, ty);
		// if (transY > 0 && x > 0 && x < SCREEN_WIDTH)
		if (tx < SPRITE_WIDTH && tx >= 0 && ty < SPRITE_HEIGHT && ty >= 0)
		{
			get_color(&wolf->sprite[CURRENT_SPRITE], &wolf->color, tx, ty);
			if ((wolf->color.r != 152 || wolf->color.g != 0 || wolf->color.b != 136))
				set_pixel(wolf, &wolf->color, x, y);
		}
	}
}
