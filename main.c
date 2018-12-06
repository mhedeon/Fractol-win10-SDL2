/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:08:38 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/16 17:23:47 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*(s1 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	if (*(s1 + i) != *(s2 + i))
		return (0);
	return (1);
}

int			main(void)
{
	t_sdl sdl;
	SDL_Event event;
	
	init_mm_window(&sdl, "Main menu)))))");
	while (1)
	{
		if (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				break;
		SDL_PumpEvents();
		if (sdl.keyboard[SDL_SCANCODE_ESCAPE])
			break;
		deal_mouse_mm(&sdl);
		/*mlx_mouse_hook(mlx.win_ptr, deal_mouse_mm, &mlx);
		mlx_hook(mlx.win_ptr, 17, 1L << 17, exit_mm, NULL);
		mlx_loop(mlx.mlx_ptr);*/
	}
	destroy_window(&sdl);
	return (0);
}
