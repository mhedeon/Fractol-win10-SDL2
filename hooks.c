/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:24:47 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/20 21:22:43 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		deal_key_mm(int key, t_sdl *sdl)
{
	if (key == 123132)
	{
		destroy_window(sdl);
		exit_mm();
	}
	return (1);
}

int		deal_mouse_mm(t_sdl *sdl)
{
	int x, y;
	SDL_Event event;
	SDL_GetMouseState(&x, &y);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			if ((x > 175 && x < 338) && (y > 251 && y < 314))
				window("Tricorn");
			else if ((x > 175 && x < 338) && (y > 337 && y < 399))
				window("Bocal");
			else if ((x > 175 && x < 338) && (y > 424 && y < 487))
				window("Mushroom");
			else if ((x > 175 && x < 338) && (y > 510 && y < 572))
				window("Perpendicular Mandelbrot");
			else if ((x > 461 && x < 624) && (y > 251 && y < 314))
				window("Julia set");
			else if ((x > 461 && x < 624) && (y > 337 && y < 399))
				window("Mandelbrot set");
			else if ((x > 461 && x < 624) && (y > 424 && y < 487))
				window("Burning ship");
			else if ((x > 461 && x < 624) && (y > 510 && y < 572))
				window("Black hole");
		}
	}
	return (1);
}

int		deal_key(t_sdl *sdl)
{
	if (sdl->keyboard[SDL_SCANCODE_KP_PLUS])
		sdl->fract->max_itter += 100;
	else if (sdl->keyboard[SDL_SCANCODE_KP_MINUS])
		sdl->fract->max_itter = (sdl->fract->max_itter - 100) < 60 ?
		sdl->fract->max_itter : sdl->fract->max_itter - 100;
	else if (sdl->keyboard[SDL_SCANCODE_SPACE])
		sdl->fract->j_move *= -1;
	/*else if (sdl->keyboard[SDL_SCANCODE_H])
		sdl->help *= -1;*/
	else if (sdl->keyboard[SDL_SCANCODE_R])
		init_fract(sdl);
	else if (sdl->keyboard[SDL_SCANCODE_RIGHT])
		sdl->fract->color = (sdl->fract->color + 1) % 7;
	else if (sdl->keyboard[SDL_SCANCODE_LEFT])
		sdl->fract->color = sdl->fract->color == 0 ?
		6 : sdl->fract->color - 1;
	else
		move_fract(sdl, sdl->fract);
	//ft_bzero((void *)mlx->img->img, mlx->img->size * WIN_HEIGHT);
	draw_fract(sdl);

	return (1);
}

int		deal_mouse(SDL_Event event, int x, int y, t_sdl *sdl)
{
	if (event.wheel.y < 0)
	{
		if (sdl->fract->delta_re < sdl->fract->ds_re ||
			sdl->fract->delta_im < sdl->fract->ds_im)
			sdl->fract->max_itter -= 1;
		good_zoom(sdl->fract, 0.93, x, WIN_HEIGHT - y);
	}
	else if (event.wheel.y > 0)
	{
		if (sdl->fract->delta_re < sdl->fract->ds_re ||
			sdl->fract->delta_im < sdl->fract->ds_im)
			sdl->fract->max_itter += 1;
		good_zoom(sdl->fract, 1.07, x, WIN_HEIGHT - y);
	}
	//ft_bzero((void *)mlx->img->img, mlx->img->size * WIN_HEIGHT);
	draw_fract(sdl);
	return (1);
}
