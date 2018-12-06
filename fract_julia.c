/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_julia.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 16:21:35 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/16 18:46:24 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			init_julia(t_sdl *sdl, t_fract *fract)
{
	fract->min_re = -1.5;
	fract->max_re = 1.5;
	fract->min_im = -1.0;
	fract->max_im = fract->min_im + (fract->max_re -
					fract->min_re) * WIN_HEIGHT / WIN_WIDTH;
	fract->ds_re = fract->max_re - fract->min_re;
	fract->ds_im = fract->max_im - fract->min_im;
	fract->delta_re = fract->ds_re;
	fract->delta_im = fract->ds_im;
	fract->j_re = -0.586000;
	fract->j_im = 0.474000;
	fract->j_move = -1;
	fract->max_itter = 100;
	fract->color = 6;
	sdl->help = -1;
}

static int		j_itter(t_fract *fract, t_z *z, int x, int y)
{
	int			i;
	double		tmp_re;
	double		tmp_im;

	z->z_re = fract->min_re + x * (fract->max_re -
				fract->min_re) / (WIN_WIDTH - 1);
	z->z_im = fract->max_im - y * (fract->max_im -
				fract->min_im) / (WIN_HEIGHT - 1);
	i = -1;
	while (++i < fract->max_itter)
	{
		tmp_re = z->z_re;
		tmp_im = z->z_im;
		z->z_re = tmp_re * tmp_re - tmp_im * tmp_im + z->c_re;
		z->z_im = 2 * tmp_re * tmp_im + z->c_im;
		z->mod = z->z_re * z->z_re + z->z_im * z->z_im;
		if (z->mod > 4)
			return (color(fract, z, i));
	}
	return (0);
}

static void		julia(t_sdl *sdl)
{
	int			x;
	int			y;
	int			start;
	t_z			z;

	start = sdl->start;
	y = start - 1;
	z.c_re = sdl->fract->j_re;
	z.c_im = sdl->fract->j_im;
	while (++y < WIN_HEIGHT / THREADS + start)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			sdl->buff[y * WIN_WIDTH + x] = j_itter(sdl->fract, &z, x, y);
		}
	}
}

void			draw_julia(t_sdl *sdl)
{
	t_sdl	c_sdl[THREADS];
	SDL_Thread	*thread[THREADS];
	int data;

	for (int i = 0; i < THREADS; i++)
	{
		c_sdl[i] = *sdl;
		c_sdl[i].start = i * WIN_HEIGHT / THREADS;
		thread[i] = SDL_CreateThread(julia, "julia", (void *)&c_sdl[i]);
	}
	for (int i = 0; i < THREADS; i++)
	{
		SDL_WaitThread(thread[i], &data);
		//printf("Thread[%d] result: %d\n", i, data);
	}

	sdl->start = 0;
	julia(sdl);
	SDL_UpdateTexture(sdl->tex, NULL, sdl->buff, WIN_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}
