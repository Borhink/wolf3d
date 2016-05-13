/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 10:19:00 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/07 15:43:57 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_x(t_env *e, t_vect2i a, t_vect2i b, int c)
{
	t_vect2i	diff;
	int			err;

	err = b.x - a.x;
	diff = set_vect2i(err * 2, ft_abs(b.y - a.y) * 2);
	while (a.x <= b.x)
	{
		img_put_pixel(e, &(e->img), a, c);
		if ((err -= diff.y) <= 0)
		{
			a.y < b.y ? a.y++ : a.y--;
			err += diff.x;
		}
		a.x++;
	}
}

static void	draw_y(t_env *e, t_vect2i a, t_vect2i b, int c)
{
	t_vect2i	diff;
	int			err;

	err = ft_abs(b.y - a.y);
	diff = set_vect2i(err * 2, (b.x - a.x) * 2);
	while (a.y != b.y)
	{
		img_put_pixel(e, &(e->img), a, c);
		if ((err -= diff.y) <= 0)
		{
			a.x++;
			err += diff.x;
		}
		a.y < b.y ? a.y++ : a.y--;
	}
	img_put_pixel(e, &(e->img), a, c);
}

void		draw_line(t_env *e, t_vect2i a, t_vect2i b, int c)
{
	t_vect2i	diff;

	if (b.x < a.x)
	{
		diff = a;
		a = b;
		b = diff;
	}
	diff = set_vect2i(b.x - a.x, ft_abs(b.y - a.y));
	if (diff.x < diff.y)
		draw_y(e, a, b, c);
	else
		draw_x(e, a, b, c);
}
