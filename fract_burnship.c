/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_burnship.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 21:28:14 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/20 17:30:23 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			init_burnship(t_sdl *sdl, t_fract *fract)
{
	fract->min_re = -3;
	fract->max_re = 1.5;
	fract->min_im = -1.0;
	fract->max_im = fract->min_im + (fract->max_re -
					fract->min_re) * WIN_HEIGHT / WIN_WIDTH;
	fract->ds_re = fract->max_re - fract->min_re;
	fract->ds_im = fract->max_im - fract->min_im;
	fract->delta_re = fract->ds_re;
	fract->delta_im = fract->ds_im;
	fract->j_re = 0;
	fract->j_im = 0;
	fract->j_move = 0;
	fract->max_itter = 60;
	fract->color = 3;
	sdl->help = -1;
}

static Uint32		b_itter(t_fract *fract, t_z *z)
{
	int			i;
	double		tmp_re;
	double		tmp_im;

	z->z_re = 0;
	z->z_im = 0;
	i = -1;
	while (++i < fract->max_itter)
	{
		tmp_re = z->z_re;
		tmp_im = z->z_im;
		z->z_re = tmp_re * tmp_re - tmp_im * tmp_im + z->c_re;
		z->z_im = -2 * fabs(tmp_re * tmp_im) + z->c_im;
		z->mod = z->z_re * z->z_re + z->z_im * z->z_im;
		if (z->mod > 4)
			return (color(fract, z, i));
	}
	return (0);
}

static void		burnship(t_sdl *sdl)
{
	int			x;
	int			y;
	int			start;
	t_z			z;

	start = sdl->start;
	y = start - 1;
	while (++y < WIN_HEIGHT / THREADS + start)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			z.c_re = sdl->fract->min_re + x * (sdl->fract->max_re -
				sdl->fract->min_re) / (WIN_WIDTH - 1);
			z.c_im = sdl->fract->max_im - y * (sdl->fract->max_im -
				sdl->fract->min_im) / (WIN_HEIGHT - 1);
			sdl->buff[y * WIN_WIDTH + x] = b_itter(sdl->fract, &z);
		}
	}
}

void			draw_burnship(t_sdl *sdl)
{
	t_sdl	c_sdl[THREADS];
	SDL_Thread	*thread[THREADS];
	int data;

	for (int i = 0; i < THREADS; i++)
	{
		c_sdl[i] = *sdl;
		c_sdl[i].start = i * WIN_HEIGHT / THREADS;
		thread[i] = SDL_CreateThread(burnship, "burnship", (void *)&c_sdl[i]);
	}
	for (int i = 0; i < THREADS; i++)
	{
		SDL_WaitThread(thread[i], &data);
		//printf("Thread[%d] result: %d\n", i, data);
	}

	sdl->start = 0;
	burnship(sdl);
	SDL_UpdateTexture(sdl->tex, NULL, sdl->buff, WIN_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}
