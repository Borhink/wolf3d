/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 13:36:31 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/11 19:34:56 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	set_texture(t_env *e, t_texture *t, char *name)
{
	if (!(t->i = mlx_xpm_file_to_image(e->mlx, name, &(t->wth), &(t->hgt))))
	{
		ft_putstr("Texture \"");
		ft_putstr(name);
		ft_putendl("\" not found");
		exit(1);
	}
	t->d = mlx_get_data_addr(t->i, &(t->bpp), &(t->sl), &(t->edn));
}

void		create_textures(t_env *e)
{
	set_texture(e, &(e->t[0]), "img/brick.xpm");
	set_texture(e, &(e->t[1]), "img/crate.xpm");
	set_texture(e, &(e->t[2]), "img/door.xpm");
	set_texture(e, &(e->t[3]), "img/grass.xpm");
	set_texture(e, &(e->t[4]), "img/wall.xpm");
}

int			get_color(int side, t_texture *t, int pos)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				size;

	size = ((t->hgt - 1) * t->sl) + (t->wth * t->bpp / 8);
	if (pos + 2 >= size)
		pos -= t->sl;
	if (side)
	{
		r = (unsigned char)(t->d[pos + 2]) < 40 ? 0 : t->d[pos + 2] - 40;
		g = (unsigned char)(t->d[pos + 1]) < 40 ? 0 : t->d[pos + 1] - 40;
		b = (unsigned char)(t->d[pos]) < 40 ? 0 : t->d[pos] - 40;
	}
	else
	{
		r = t->d[pos + 2];
		g = t->d[pos + 1];
		b = t->d[pos];
	}
	return (r * 0x10000 + g * 0x100 + b);
}

void		draw_texture_col(t_env *e, t_view *v, t_line *l, int id)
{
	t_texture		*t;
	int				pos;
	int				y;

	t = &(e->t[id]);
	l->text_x = (int)(l->wall_x * (double)(t->wth));
	if ((v->side == 0 && v->rdir.x > 0) || (v->side == 1 && v->rdir.y < 0))
		l->text_x = t->wth - l->text_x - 1;
	y = l->start.y;
	while (y <= l->end.y)
	{
		l->d = (y - e->hgt) * 256 - WIN_H * 128 + l->line_h * 128;
		l->text_y = (l->d * t->wth / l->line_h) / 256;
		pos = t->sl * l->text_y + l->text_x * t->bpp / 8;
		l->color = get_color(v->side, t, pos);
		img_put_pixel(e, &(e->img), set_vect2i(l->x, y), l->color);
		y++;
	}
}
