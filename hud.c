/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:00:22 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/27 22:13:29 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void		show_health(t_wolf *wolf)
{
	SDL_Rect	r;
	char		*tmp;
	char		*tmp2;
	SDL_Surface	*sur;
	SDL_Texture	*message;

	tmp2 = ft_itoa(wolf->hero->health);
	tmp = ft_strjoin("+", tmp2);
	sur = TTF_RenderText_Solid(wolf->font, tmp,
			(SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = r.x / 10;
	r.h = r.x / 10;
	SDL_RenderCopy(wolf->ren, message, NULL, &(SDL_Rect)
				{r.x / 2 - 2.5 * r.w, r.y - r.h, r.w, r.h});
	free(tmp);
	free(tmp2);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

static void		show_bullet(t_wolf *wolf)
{
	SDL_Rect	r;
	char		*tmp;
	char		*tmp2;
	SDL_Surface	*sur;
	SDL_Texture	*message;

	tmp2 = ft_itoa(wolf->hero->bullet);
	tmp = ft_strjoin("\%", tmp2);
	sur = TTF_RenderText_Solid(wolf->font, tmp,
			(SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = 2 * r.x / 10;
	r.h = r.x / 10;
	SDL_RenderCopy(wolf->ren, message, NULL, &(SDL_Rect)
			{r.x / 2 + 0.75 * r.w, r.y - r.h * 0.80, r.w, r.h});
	free(tmp);
	free(tmp2);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

static void		show_score(t_wolf *wolf)
{
	SDL_Rect	r;
	char		*tmp;
	SDL_Surface	*sur;
	SDL_Texture	*message;

	tmp = ft_itoa(wolf->hero->score);
	sur = TTF_RenderText_Solid(wolf->font, tmp,
			(SDL_Color) {255, 255, 255, 255});
	message = SDL_CreateTextureFromSurface(wolf->ren, sur);
	SDL_GetWindowSize(wolf->win, &r.x, &r.y);
	r.w = r.x / 10;
	r.h = r.x / 10;
	SDL_RenderCopy(wolf->ren, message, NULL,
				&(SDL_Rect) {50, r.y - r.h, r.w, r.h});
	free(tmp);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(message);
}

void			draw_hud(t_wolf *wolf)
{
	face(wolf);
	SDL_UpdateTexture(wolf->tex, NULL, wolf->buff,
					SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(wolf->ren);
	SDL_RenderCopy(wolf->ren, wolf->tex, NULL, NULL);
	show_score(wolf);
	show_bullet(wolf);
	show_health(wolf);
}
