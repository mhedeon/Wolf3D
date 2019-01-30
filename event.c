/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:05:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/30 21:27:30 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void		poll_event(t_wolf *wolf, SDL_Event e)
{
	if (e.type == SDL_MOUSEWHEEL && e.wheel.y > 0)
		wolf->sens += (wolf->sens + 0.05) <= 1.0 ? 0.05 : 0;
	if (e.type == SDL_MOUSEWHEEL && e.wheel.y < 0)
		wolf->sens -= (wolf->sens - 0.05) > 0 ? 0.05 : 0;
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		if (wolf->weapon == 2 && wolf->hero->bullet > 0 && !wolf->shot)
		{
			wolf->shot = 1;
			wolf->hero->bullet -= 1;
		}
		else if (wolf->weapon == 1 && !wolf->shot)
			wolf->shot = 1;
	}
	if (KEY == SDLK_1 && !wolf->shot)
		wolf->weapon = 1;
	if (KEY == SDLK_2 && !wolf->shot)
		wolf->weapon = 2;
	changes(wolf, e);
}

static void		pump_event(t_wolf *wolf)
{
	wolf->ms = (wolf->keyboard[SDL_SCANCODE_LSHIFT]) ?
				wolf->ms * 1.5 : wolf->ms;
	if (wolf->keyboard[SDL_SCANCODE_W])
		step(wolf, GO_FORWARD);
	if (wolf->keyboard[SDL_SCANCODE_S])
		step(wolf, GO_BACK);
	if (wolf->keyboard[SDL_SCANCODE_A])
		strafe(wolf, STRAFE_LEFT);
	if (wolf->keyboard[SDL_SCANCODE_D])
		strafe(wolf, STRAFE_RIGHT);
}

int				event(t_wolf *wolf, int (*end)(t_wolf *wolf))
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
			return (0);
		if (KEY == SDLK_h)
			show_controls();
		poll_event(wolf, e);
	}
	rotate(wolf);
	pump_event(wolf);
	if (wolf->keyboard[SDL_SCANCODE_SPACE])
	{
		if ((*end)(wolf))
			return (0);
		else
			open_door(wolf);
	}
	return (1);
}

static void		changes_norm(t_wolf *wolf, SDL_Event e)
{
	if (KEY == SDLK_f && e.key.keysym.mod != KMOD_LSHIFT)
		SDL_SetWindowFullscreen(wolf->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else if (e.key.keysym.mod == KMOD_LSHIFT && KEY == SDLK_f)
		SDL_SetWindowFullscreen(wolf->win, 0);
	else if (KEY == SDLK_KP_PLUS)
	{
		wolf->volume += (wolf->volume + 5) > 128 ? 0 : 5;
		Mix_Volume(-1, wolf->volume);
		Mix_VolumeMusic(wolf->volume);
	}
	else if (KEY == SDLK_KP_MINUS)
	{
		wolf->volume -= (wolf->volume - 5) < 0 ? 0 : 5;
		Mix_Volume(-1, wolf->volume);
		Mix_VolumeMusic(wolf->volume);
	}
	else if (KEY == SDLK_m && e.key.keysym.mod == KMOD_LSHIFT
			&& e.key.keysym.mod != KMOD_RSHIFT)
	{
		if (Mix_VolumeMusic(-1))
			Mix_VolumeMusic(0);
		else
			Mix_VolumeMusic(wolf->volume);
	}
}

void			changes(t_wolf *wolf, SDL_Event e)
{
	if (KEY == SDLK_m && e.key.keysym.mod == KMOD_RSHIFT
			&& e.key.keysym.mod != KMOD_LSHIFT)
	{
		if (Mix_Volume(-1, -1))
			Mix_Volume(-1, 0);
		else
			Mix_Volume(-1, wolf->volume);
	}
	else if (KEY == SDLK_m && e.key.keysym.mod != KMOD_LSHIFT
			&& e.key.keysym.mod != KMOD_RSHIFT)
	{
		if (Mix_Volume(-1, -1) || Mix_VolumeMusic(-1))
		{
			Mix_Volume(-1, 0);
			Mix_VolumeMusic(0);
		}
		else
		{
			Mix_Volume(-1, wolf->volume);
			Mix_VolumeMusic(wolf->volume);
		}
	}
	else
		changes_norm(wolf, e);
}
