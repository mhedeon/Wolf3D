/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:05:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/01/23 21:08:08 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int event(t_wolf *wolf)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
			return (0);
		if (e.type == SDL_MOUSEWHEEL && e.wheel.y > 0)
			wolf->sens += (wolf->sens + 0.05) <= 1.0
									? 0.05 : 0;
		if (e.type == SDL_MOUSEWHEEL && e.wheel.y < 0)
			wolf->sens -= (wolf->sens - 0.05) > 0
									? 0.05 : 0;
		changes(wolf, e);
	}
	rotate(wolf);
	changes(wolf, e);
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
	if (wolf->keyboard[SDL_SCANCODE_SPACE])
		open_door(wolf);
	return (1);
}

void open_door(t_wolf *wolf)
{
	if (cast_door(wolf) && (abs((int)wolf->p_x - wolf->m_x) +
			abs((int)wolf->p_y - wolf->m_y)) <= 2.0 &&
			wolf->door.opened == 0)
		{
			printf("qwe\n");
			wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].d = 0;
			wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].c = 0;
			wolf->door.x = wolf->m_x;
			wolf->door.y = wolf->m_y;
			if (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 52 ||
				wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 54 ||
				wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].north == 55)
			wolf->door.opened = 1;
		}
}

void close_door(t_wolf *wolf)
{
	if ((wolf->p_x > (wolf->door.x - 1.0) && wolf->p_x < (wolf->door.x + 2.0)) &&
		(wolf->p_y > (wolf->door.y - 1.0) && wolf->p_y < (wolf->door.y + 2.0)))
		return ;
	printf("p_x: %f | p_y: %f\nx: %d | y: %d\n", wolf->p_x, wolf->p_y, wolf->door.x, wolf->door.y);
	wolf->map[wolf->door.y * wolf->m_width + wolf->door.x].d = 1;
	wolf->map[wolf->door.y * wolf->m_width + wolf->door.x].c = 1;
	wolf->door.opened = 0;
}

void changes(t_wolf *wolf, SDL_Event e)
{
	if (KEY == SDLK_f && e.key.keysym.mod != KMOD_LSHIFT)
		SDL_SetWindowFullscreen(wolf->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else if (e.key.keysym.mod == KMOD_LSHIFT && KEY == SDLK_f)
		SDL_SetWindowFullscreen(wolf->win, 0);
	else if (KEY == SDLK_KP_PLUS)
	{
		wolf->volume += (wolf->volume + 5) > 128 ? 0 : 5;
		printf("%d\n", wolf->volume);
		Mix_Volume(1, wolf->volume);
		Mix_VolumeMusic(wolf->volume);

	}
	else if (KEY == SDLK_KP_MINUS)
	{
		wolf->volume -= (wolf->volume - 5) < 0 ? 0 : 5;
		printf("%d\n", wolf->volume);
		Mix_Volume(1, wolf->volume);
		Mix_VolumeMusic(wolf->volume);
	}
	else if (KEY == SDLK_m && e.key.keysym.mod != KMOD_LSHIFT && e.key.keysym.mod != KMOD_RSHIFT)
	{
		if (Mix_Volume(1, -1) || Mix_VolumeMusic(-1))
		{
			Mix_Volume(1, 0);
			Mix_VolumeMusic(0);
		}
		else
		{
			Mix_Volume(1, wolf->volume);
			Mix_VolumeMusic(wolf->volume);
		}
	}
	else if (KEY == SDLK_m && e.key.keysym.mod == KMOD_LSHIFT && e.key.keysym.mod != KMOD_RSHIFT)
	{
		if (Mix_VolumeMusic(-1))
			Mix_VolumeMusic(0);
		else
			Mix_VolumeMusic(wolf->volume);
	}
	else if (KEY == SDLK_m && e.key.keysym.mod == KMOD_RSHIFT && e.key.keysym.mod != KMOD_LSHIFT)
	{
		if (Mix_Volume(1, -1))
			Mix_Volume(1, 0);
		else
			Mix_Volume(1, wolf->volume);
	}
}
