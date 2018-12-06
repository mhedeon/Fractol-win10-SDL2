/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:08:54 by mhedeon           #+#    #+#             */
/*   Updated: 2018/08/20 17:34:56 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <SDL.h>
# include <SDL_image.h>

# define THREADS		8

# define MM_WIDTH		798
# define MM_HEIGHT		599

# define WIN_WIDTH		800
# define WIN_HEIGHT		600
# define HELP_WIDTH		350
# define HELP_HEIGHT	400

typedef struct	s_rgb
{
	Uint32			r;
	Uint32			g;
	Uint32			b;
}				t_rgb;

typedef struct	s_hsv
{
	double		h;
	double		s;
	double		v;
	int			hi;
	double		p;
	double		q;
	double		t;
}				t_hsv;

typedef struct	s_z
{
	double		z_re;
	double		z_im;
	double		c_re;
	double		c_im;
	double		mod;
}				t_z;

typedef struct	s_fract
{
	double		max_re;
	double		min_re;
	double		max_im;
	double		min_im;
	double		mouse_re;
	double		mouse_im;
	double		j_re;
	double		j_im;
	double		delta_re;
	double		delta_im;
	double		ds_re;
	double		ds_im;
	int			j_move;
	int			max_itter;
	int			color;
}				t_fract;

typedef struct	s_img
{
	int			end;
	int			bits;
	int			size;
	char		*img;
	void		*img_ptr;
}				t_img;

typedef struct	s_sdl
{
	
	SDL_Window	*win;
	SDL_Renderer	*ren;
	SDL_Texture	*tex;
	const Uint8	*keyboard;
	Uint32		*buff;
	t_fract		*fract;
	char		*win_name;
	int			start;
	int			help;
}				t_sdl;

int			ft_strequ(char const *s1, char const *s2);

/*
** init.c
*/
int				exit_win(void);
int				exit_mm(void);
void	init_window(t_sdl *sdl, t_fract *fract, char *win_name);
void	init_mm_window(t_sdl *sdl, char *win_name);
void	destroy_window(t_sdl *sdl);

/*
** hooks.c
*/
int		deal_key_mm(int key, t_sdl *sdl);
int		deal_mouse_mm(t_sdl *sdl);
int		deal_key(t_sdl *sdl);
int		deal_mouse(SDL_Event event, int x, int y, t_sdl *sdl);

/*
** rotate.c
*/
void		move_fract(t_sdl *sdl, t_fract *fract);
double			interpolate(double start, double end, double interpolation);
int			j_mouse_change(int x, int y, t_sdl *sdl);
void			good_zoom(t_fract *fract, double zoom, int x, int y);

/*
** draw.c
*/
void		init_fract(t_sdl *sdl);
void		draw_fract(t_sdl *sdl);
void			window(char *win_name);
int		deal_key_mm(int key, t_sdl *sdl);

/*
** color1.c
*/
int				dark(t_fract *fract, int i);
int				lsd1(t_z *z, int i);
int				lsd2(t_fract *fract, t_z *z, int i);
int				red(t_fract *fract, int i);

/*
** color2.c
*/
int				toxic1(t_fract *fract, int i);
int				toxic2(t_fract *fract, int i);
int				toxic3(t_fract *fract, int i);
int				color(t_fract *fract, t_z *z, int i);

/*
** hsv2rgb.c
*/
int				hsv2rgb(int h, double s, double v);

/*
** fract_mandelbrot.c
*/
void			draw_mandelbrot(t_sdl *sdl);
void			init_mandelbrot(t_sdl *sdl, t_fract *fract);

/*
** fract_julia.c
*/
void			draw_julia(t_sdl *sdl);
void			init_julia(t_sdl *sdl, t_fract *fract);

/*
** fract_burnship.c
*/
void			draw_burnship(t_sdl *sdl);
void			init_burnship(t_sdl *sdl, t_fract *fract);

/*
** fract_blackhole.c
*/
void			draw_blackhole(t_sdl *sdl);
void			init_blackhole(t_sdl *sdl, t_fract *fract);

/*
** fract_mushroom.c
*/
void			draw_mushroom(t_sdl *sdl);
void			init_mushroom(t_sdl *sdl, t_fract *fract);

/*
** fract_bocal.c
*/
void			draw_bocal(t_sdl *sdl);
void			init_bocal(t_sdl *sdl, t_fract *fract);

/*
** fract_tricorn.c
*/
void		draw_tricorn(t_sdl *sdl);
void		init_tricorn(t_sdl *sdl, t_fract *fract);

/*
** fract_perpmand
*/
void			draw_perpmand(t_sdl *sdl);
void			init_perpmand(t_sdl *sdl, t_fract *fract);

#endif
