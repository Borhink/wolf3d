/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcaster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:25:45 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/11 17:55:29 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	create_floorcaster(t_view *v, t_line *l, t_floor *f)
{
	if (v->side == 0 && v->rdir.x > 0)
		f->wall = set_vect2d(v->map.x, v->map.y + l->wall_x);
	else if (v->side == 0 && v->rdir.x < 0)
		f->wall = set_vect2d(v->map.x + 1.0, v->map.y + l->wall_x);
	else if (v->side == 1 && v->rdir.y > 0)
		f->wall = set_vect2d(v->map.x + l->wall_x, v->map.y);
	else
		f->wall = set_vect2d(v->map.x + l->wall_x, v->map.y + 1.0);
	f->dwall = v->pwall;
	f->dplayer = 0.0;
}

void		draw_floor(t_env *e, t_view *v, t_line *l)
{
	t_floor		f;
	int			y;
	int			pos;
	int			color;

	create_floorcaster(v, l, &f);
	if (l->end.y < 0)
		l->end.y = WIN_H;
	y = l->end.y;
	while (++y < WIN_H)
	{
		f.cur_d = WIN_H / (2.0 * (y - e->hgt) - WIN_H);
		f.weight = (f.cur_d - f.dplayer) / (f.dwall - f.dplayer);
		f.cur.x = f.weight * f.wall.x + (1.0 - f.weight) * v->pos.x;
		f.cur.y = f.weight * f.wall.y + (1.0 - f.weight) * v->pos.y;
		f.text.x = (int)(f.cur.x * e->t[3].wth) % e->t[3].wth;
		f.text.y = (int)(f.cur.y * e->t[3].hgt) % e->t[3].hgt;
		pos = e->t[3].sl * f.text.y + f.text.x * e->t[3].bpp / 8;
		color = get_color(0, &(e->t[3]), pos);
		img_put_pixel(e, &(e->img), set_vect2i(l->x, y), color);
	}
}
