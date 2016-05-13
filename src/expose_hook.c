/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 00:56:03 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/12 00:40:30 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		img_put_pixel(t_env *e, t_img *i, t_vect2i p, int c)
{
	int		pos;
	int		size;

	size = ((WIN_H - 1) * e->img.sl) + (WIN_W * e->img.bpp / 8);
	pos = (p.y * i->sl) + (p.x * i->bpp / 8);
	if (pos > 0 && pos + 2 < size && p.x >= 0
		&& (p.x * e->img.bpp / 8) < e->img.sl)
	{
		if (i->edn)
		{
			i->d[pos] = mlx_get_color_value(e->mlx, c / 0x10000 % 0x100);
			i->d[pos + 1] = mlx_get_color_value(e->mlx, c / 0x100 % 0x100);
			i->d[pos + 2] = mlx_get_color_value(e->mlx, c % 0x100);
		}
		else
		{
			i->d[pos] = mlx_get_color_value(e->mlx, c % 0x100);
			i->d[pos + 1] = mlx_get_color_value(e->mlx, c / 0x100 % 0x100);
			i->d[pos + 2] = mlx_get_color_value(e->mlx, c / 0x10000 % 0x100);
		}
	}
}

static void	clear_img(t_img *i)
{
	t_vect2i	p;
	int			pos;

	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			pos = (p.y * i->sl) + (p.x * i->bpp / 8);
			i->d[pos] = 0;
			i->d[pos + 1] = 0;
			i->d[pos + 2] = 0;
		}
	}
}

int			expose_hook(void *env)
{
	t_env	*e;

	e = (t_env*)env;
	clear_img(&(e->img));
	game_render(e, &(e->view));
	draw_minimap(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img.i, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->hand.i, e->handp.x, e->handp.y);
	return (1);
}
