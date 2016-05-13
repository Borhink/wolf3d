/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 11:42:09 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/12 15:30:30 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	create_render(t_view *v, int x)
{
	v->cam = 2 * x / (double)(WIN_W) - 1;
	v->rpos.x = v->pos.x;
	v->rpos.y = v->pos.y;
	v->rdir.x = v->dir.x + v->plane.x * v->cam;
	v->rdir.y = v->dir.y + v->plane.y * v->cam;
	v->map.x = (int)(v->rpos.x);
	v->map.y = (int)(v->rpos.y);
	v->delta.x = sqrt(1 + (v->rdir.y * v->rdir.y) / (v->rdir.x * v->rdir.x));
	v->delta.y = sqrt(1 + (v->rdir.x * v->rdir.x) / (v->rdir.y * v->rdir.y));
	v->hit = 0;
}

static void	get_sidedist(t_view *v)
{
	if (v->rdir.x < 0)
	{
		v->step.x = -1;
		v->sdist.x = (v->rpos.x - v->map.x) * v->delta.x;
	}
	else
	{
		v->step.x = 1;
		v->sdist.x = (v->map.x + 1.0 - v->rpos.x) * v->delta.x;
	}
	if (v->rdir.y < 0)
	{
		v->step.y = -1;
		v->sdist.y = (v->rpos.y - v->map.y) * v->delta.y;
	}
	else
	{
		v->step.y = 1;
		v->sdist.y = (v->map.y + 1.0 - v->rpos.y) * v->delta.y;
	}
}

static int	find_wall(t_env *e, t_view *v)
{
	while (!v->hit)
	{
		if (v->sdist.x < v->sdist.y)
		{
			v->sdist.x += v->delta.x;
			v->map.x += v->step.x;
			v->side = 0;
		}
		else
		{
			v->sdist.y += v->delta.y;
			v->map.y += v->step.y;
			v->side = 1;
		}
		if (v->map.y >= e->map.size.y || v->map.x >= e->map.size.x
		|| v->map.x < 0 || v->map.y < 0)
			return (0);
		if (e->map.map[v->map.y][v->map.x] > 0)
			v->hit = 1;
	}
	if (!v->side)
		v->pwall = (v->map.x - v->rpos.x + (1 - v->step.x) / 2) / v->rdir.x;
	else
		v->pwall = (v->map.y - v->rpos.y + (1 - v->step.y) / 2) / v->rdir.y;
	return (1);
}

static void	to_draw(t_env *e, t_view *v, t_line *l)
{
	l->start.x = l->x;
	l->end.x = l->x;
	l->color = 0;
	if (v->side == 0)
		l->wall_x = v->rpos.y + v->pwall * v->rdir.y;
	else
		l->wall_x = v->rpos.x + v->pwall * v->rdir.x;
	l->wall_x -= floor(l->wall_x);
	if (e->map.map[v->map.y][v->map.x] > 1
	&& e->map.map[v->map.y][v->map.x] < 11)
		draw_texture_col(e, v, l, e->map.map[v->map.y][v->map.x] - 2);
	else if (e->map.map[v->map.y][v->map.x] > 11
	&& e->map.map[v->map.y][v->map.x] <= 16)
		draw_texture_col(e, v, l, e->map.map[v->map.y][v->map.x] - 12);
	else
	{
		if (v->side == 0)
			l->color = (v->step.x == -1 ? 0xaa0000 : 0xaaaa00);
		if (v->side == 1)
			l->color = (v->step.y == -1 ? 0xaa00 : 0xaa);
		draw_line(e, l->start, l->end, l->color);
	}
	if (l->start.y > 0)
		draw_line(e, set_vect2i(l->x, 0), l->start, 0x2E9AFE);
	draw_floor(e, v, l);
}

void		game_render(t_env *e, t_view *v)
{
	t_line		l;

	l.x = -1;
	while (++l.x < WIN_W)
	{
		create_render(v, l.x);
		get_sidedist(v);
		if (find_wall(e, v))
		{
			l.line_h = (int)(WIN_H / v->pwall);
			if ((l.start.y = -l.line_h / 2 + WIN_H / 2 + (int)e->hgt) < 0)
				l.start.y = 0;
			if ((l.end.y = l.line_h / 2 + WIN_H / 2 + (int)e->hgt) >= WIN_H)
				l.end.y = WIN_H - 1;
			to_draw(e, v, &l);
		}
	}
}
