/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:12:34 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/16 18:31:58 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		exit_mm(void)
{
	exit(1);
}

int		exit_win(void)
{
	return (1);
}

void	destroy_window(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	free(sdl->buff);
}

void	init_mm_window(t_sdl *sdl, char *win_name)
{
	int	a;
	int	b;
	SDL_Surface *surface = IMG_Load("menu.jpg");

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	sdl->win = SDL_CreateWindow(win_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MM_WIDTH, MM_HEIGHT, SDL_WINDOW_SHOWN);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	sdl->tex = SDL_CreateTextureFromSurface(sdl->ren, surface);
	sdl->keyboard = SDL_GetKeyboardState(NULL);
	sdl->buff = (Uint32 *)malloc(sizeof(Uint32) * (MM_WIDTH * MM_HEIGHT));
	SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}

void	init_window(t_sdl *sdl, t_fract *fract, char *win_name)
{
	/*if (ft_strequ(win_name, "Help"))
	{
		mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
					HELP_WIDTH, HELP_HEIGHT, win_name);
		img = NULL;
	}*/
	//else
	{
		sdl->win = SDL_CreateWindow(win_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
		sdl->tex = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT);
		sdl->fract = fract;
		sdl->win_name = win_name;
		sdl->keyboard = SDL_GetKeyboardState(NULL);
		sdl->buff = (Uint32 *)malloc(sizeof(Uint32) * (WIN_WIDTH * WIN_HEIGHT));
	}
}
