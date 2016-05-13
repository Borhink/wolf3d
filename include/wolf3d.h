/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:17:17 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/13 18:03:45 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <math.h>
# include "includes/libft.h"
# include "mlx.h"

# define WIN_W 1280
# define WIN_H (1280 * 9 / 16)

# define MOTION_MASK (1L<<6)
# define KEYPRESS_MASK (1L<<0)
# define KEYRELEASE_MASK (1L<<1)
# define STRUCTURE_NOTIFY_MASK (1L<<17)
# define MOTION_NOTIFY 6
# define KEYPRESS 2
# define KEYRELEASE 3
# define DESTROYNOTIFY 17

typedef struct s_vect2d		t_vect2d;
typedef struct s_vect2i		t_vect2i;
typedef struct s_img		t_img;
typedef struct s_texture	t_texture;
typedef struct s_keys		t_keys;
typedef struct s_view		t_view;
typedef struct s_map		t_map;
typedef struct s_line		t_line;
typedef struct s_floor		t_floor;
typedef struct s_env		t_env;

struct		s_vect2d
{
	double	x;
	double	y;
};

struct		s_vect2i
{
	int		x;
	int		y;
};

struct		s_img
{
	void	*i;
	char	*d;
	int		bpp;
	int		sl;
	int		edn;
};

struct		s_texture
{
	void	*i;
	char	*d;
	int		bpp;
	int		sl;
	int		edn;
	int		hgt;
	int		wth;
};

struct		s_keys
{
	int		up;
	int		left;
	int		right;
	int		down;
	int		walk;
	int		lookup;
	int		lookdown;
};

struct		s_view
{
	t_vect2d	pos;
	t_vect2d	dir;
	t_vect2d	plane;
	t_vect2d	rpos;
	t_vect2d	rdir;
	t_vect2i	map;
	t_vect2i	step;
	t_vect2d	sdist;
	t_vect2d	delta;
	double		cam;
	double		pwall;
	int			hit;
	int			side;
};

struct		s_map
{
	t_vect2i	size;
	int			**map;
};

struct		s_line
{
	t_vect2i	start;
	t_vect2i	end;
	int			x;
	int			text_x;
	int			text_y;
	double		wall_x;
	int			color;
	int			line_h;
	int			d;
	int			tmp;
};

struct		s_floor
{
	t_vect2d	wall;
	t_vect2d	cur;
	t_vect2i	text;
	double		dwall;
	double		dplayer;
	double		cur_d;
	double		weight;
};

struct		s_env
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_view		view;
	t_keys		key;
	t_texture	t[5];
	t_texture	hand;
	t_vect2i	handp;
	double		spd;
	double		hgt;
};

t_vect2d	set_vect2d(double x, double y);
t_vect2i	set_vect2i(int x, int y);
int			create_img(t_env *e, t_img *img);

int			key_pressed(int key, void *env);
int			key_released(int key, void *env);
int			apply_event(void *env);
int			window_destroyed(void *env);
int			expose_hook(void *env);

void		img_put_pixel(t_env *d, t_img *i, t_vect2i p, int c);
void		draw_line(t_env *e, t_vect2i a, t_vect2i b, int c);
int			create_map(t_map *m);
void		free_map(t_map *m);

void		game_render(t_env *e, t_view *v);
void		draw_texture_col(t_env *e, t_view *v, t_line *l, int id);
void		draw_floor(t_env *e, t_view *v, t_line *l);
void		draw_ceil(t_env *e, t_view *v, t_line *l);
void		draw_minimap(t_env *e);
void		create_textures(t_env *e);
int			get_color(int side, t_texture *t, int pos);

#endif
