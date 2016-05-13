/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:47:26 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/12 00:27:37 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_move_up(t_env *e, t_view *v)
{
	if ((int)(v->pos.x + v->dir.x * 0.19) < e->map.size.x
	&& (int)(v->pos.x + v->dir.x * 0.19) >= 0
	&& (!e->map.map[(int)v->pos.y][(int)(v->pos.x + v->dir.x * 0.19)]
	|| e->map.map[(int)v->pos.y][(int)(v->pos.x + v->dir.x * 0.19)] > 9))
		v->pos.x += v->dir.x * e->spd;
	if ((int)(v->pos.y + v->dir.y * 0.19) < e->map.size.y
	&& (int)(v->pos.y + v->dir.y * 0.19) >= 0
	&& (!e->map.map[(int)(v->pos.y + v->dir.y * 0.19)][(int)v->pos.x]
	|| e->map.map[(int)(v->pos.y + v->dir.y * 0.19)][(int)v->pos.x] > 9))
		v->pos.y += v->dir.y * e->spd;
}

static void	ft_move_down(t_env *e, t_view *v)
{
	if ((int)(v->pos.x - v->dir.x * 0.19) < e->map.size.x
	&& (int)(v->pos.x - v->dir.x * 0.19) >= 0
	&& (!e->map.map[(int)v->pos.y][(int)(v->pos.x - v->dir.x * 0.19)]
	|| e->map.map[(int)v->pos.y][(int)(v->pos.x - v->dir.x * 0.19)] > 9))
		v->pos.x -= v->dir.x * e->spd;
	if ((int)(v->pos.y - v->dir.y * 0.19) < e->map.size.y
	&& (int)(v->pos.y - v->dir.y * 0.19) >= 0
	&& (!e->map.map[(int)(v->pos.y - v->dir.y * 0.19)][(int)v->pos.x]
	|| e->map.map[(int)(v->pos.y - v->dir.y * 0.19)][(int)v->pos.x] > 9))
		v->pos.y -= v->dir.y * e->spd;
}

static void	ft_rot(t_env *e, t_view *v)
{
	double	tmp_dir;
	double	tmp_plane;

	if (e->key.left)
	{
		tmp_dir = v->dir.x;
		v->dir.x = v->dir.x * cos(-0.08) - v->dir.y * sin(-0.08);
		v->dir.y = tmp_dir * sin(-0.08) + v->dir.y * cos(-0.08);
		tmp_plane = v->plane.x;
		v->plane.x = v->plane.x * cos(-0.08) - v->plane.y * sin(-0.08);
		v->plane.y = tmp_plane * sin(-0.08) + v->plane.y * cos(-0.08);
	}
	if (e->key.right)
	{
		tmp_dir = v->dir.x;
		v->dir.x = v->dir.x * cos(0.08) - v->dir.y * sin(0.08);
		v->dir.y = tmp_dir * sin(0.08) + v->dir.y * cos(0.08);
		tmp_plane = v->plane.x;
		v->plane.x = v->plane.x * cos(0.08) - v->plane.y * sin(0.08);
		v->plane.y = tmp_plane * sin(0.08) + v->plane.y * cos(0.08);
	}
}

static void	ft_look(t_env *e)
{
	if (e->key.lookdown)
		e->hgt += (e->hgt > -240 ? -60 : 0);
	else
		e->hgt += (e->hgt < 0 ? 60 : 0);
	if (e->key.lookup && e->hgt > -240)
		e->hgt += (e->hgt < 360 ? 60 : 0);
	else
		e->hgt += (e->hgt > 0 ? -60 : 0);
	e->handp.y = WIN_H - 100 + e->hgt;
}

int			apply_event(void *env)
{
	t_env	*e;
	t_view	*v;
	int		lk;

	e = (t_env*)env;
	v = &(e->view);
	lk = e->hgt;
	if (e->key.up)
		ft_move_up(e, v);
	if (e->key.down)
		ft_move_down(e, v);
	if (e->key.right || e->key.left)
		ft_rot(e, v);
	e->spd = (e->key.walk ? 0.06 : 0.12);
	ft_look(e);
	if (e->key.up || e->key.down || e->key.left || e->key.right || e->hgt != lk)
		expose_hook((void*)e);
	return (1);
}
