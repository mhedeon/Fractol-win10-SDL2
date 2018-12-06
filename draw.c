/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 17:23:47 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/22 18:17:14 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <stdio.h>

void		init_fract(t_sdl *sdl)
{
	if (ft_strequ(sdl->win_name, "Tricorn"))
		init_tricorn(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Bocal"))
		init_bocal(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Mushroom"))
		init_mushroom(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Perpendicular Mandelbrot"))
		init_perpmand(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Julia set"))
		init_julia(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Mandelbrot set"))
		init_mandelbrot(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Burning ship"))
		init_burnship(sdl, sdl->fract);
	else if (ft_strequ(sdl->win_name, "Black hole"))
		init_blackhole(sdl, sdl->fract);
	draw_fract(sdl);
}

void		draw_fract(t_sdl *sdl)
{
	sdl->fract->delta_re = sdl->fract->max_re - sdl->fract->min_re;
	sdl->fract->delta_im = sdl->fract->max_im - sdl->fract->min_im;
	if (ft_strequ(sdl->win_name, "Tricorn"))
		draw_tricorn(sdl);
	else if (ft_strequ(sdl->win_name, "Bocal"))
		draw_bocal(sdl);
	else if (ft_strequ(sdl->win_name, "Mushroom"))
		draw_mushroom(sdl);
	else if (ft_strequ(sdl->win_name, "Perpendicular Mandelbrot"))
		draw_perpmand(sdl);
	else if (ft_strequ(sdl->win_name, "Julia set"))
		draw_julia(sdl);
	else if (ft_strequ(sdl->win_name, "Mandelbrot set"))
		draw_mandelbrot(sdl);
	else if (ft_strequ(sdl->win_name, "Burning ship"))
		draw_burnship(sdl);
	else if (ft_strequ(sdl->win_name, "Black hole"))
		draw_blackhole(sdl);
}

void		window(char *win_name)
{
	t_sdl	sdl;
	t_fract	fract;
	SDL_Event event;
	int x, y;

	init_window(&sdl, &fract, win_name);
	init_fract(&sdl);
	while (1)
	{
		SDL_GetMouseState(&x, &y);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break;
			if (event.type == SDL_MOUSEMOTION)
			{
				j_mouse_change(x, y, &sdl);
			}
			if (event.type == SDL_MOUSEWHEEL)
			{
				deal_mouse(event, x, y, &sdl);
			}
		}

		SDL_PumpEvents();
		if (sdl.keyboard[SDL_SCANCODE_ESCAPE])
			break;
		deal_key(&sdl);
	}
	SDL_Delay(100000);
	destroy_window(&sdl);
	//return;
}

void		help(t_sdl *sdl)
{
	/*mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 330, 0x00f900, "Move: W, A, S, D");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 360, 0x00f900, "Zoom: MOUSE WHEEL");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 390, 0x00f900, "Change color: ARROWS");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 420, 0x00f900, "Reset: R");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 450, 0x00f900, "Iterations: +, -");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 480, 0x00f900, "Interactive mode: SPACE [on/off]");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 500, 0x00f900, "(for Julia and Black hole only)");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					30, 550, 0x00f900, "Exit: ESC");*/
}
