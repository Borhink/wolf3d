/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 20:54:51 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/12 02:28:32 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void	create_minimap(t_env *e)
{
	t_vect2i	p;

	p.y = e->handp.y + 37;
	while (++p.y < e->handp.y + 296)
	{
		p.x = e->handp.x + 110;
		while (++p.x < e->handp.x + 455)
			img_put_pixel(e, &(e->img), p, 0x777777);
	}
}

static void	add_wall(t_env *e, t_vect2i pos)
{
	t_vect2i	p;
	t_vect2i	end;

	p = set_vect2i(e->handp.x + 113 + pos.x * 10, e->handp.y + 37 + pos.y * 10);
	end = set_vect2i(p.x + 10, p.y + 10);
	while (++p.y < end.y)
	{
		p.x = end.x - 10;
		while (++p.x < end.x)
		{
			if (e->map.map[pos.y][pos.x] == 1)
				img_put_pixel(e, &(e->img), p, 0xffffff);
			else if (e->map.map[pos.y][pos.x] == 2)
				img_put_pixel(e, &(e->img), p, 0x863130);
			else if (e->map.map[pos.y][pos.x] == 3)
				img_put_pixel(e, &(e->img), p, 0x6B5027);
			else if (e->map.map[pos.y][pos.x] == 4)
				img_put_pixel(e, &(e->img), p, 0x918787);
			else if (e->map.map[pos.y][pos.x] == 6)
				img_put_pixel(e, &(e->img), p, 0x434343);
		}
	}
}

static void	add_player(t_env *e)
{
	t_vect2i	player;
	t_vect2i	p;

	player.x = e->handp.x + 113 + (int)(e->view.pos.x) * 10;
	player.y = e->handp.y + 37 + (int)(e->view.pos.y) * 10;
	p.y = player.y;
	while (++p.y < player.y + 10)
	{
		p.x = player.x;
		while (++p.x < player.x + 10)
			img_put_pixel(e, &(e->img), p, 0x00dd00);
	}
}

void		draw_minimap(t_env *e)
{
	t_vect2i	p;

	create_minimap(e);
	p.y = -1;
	while (++p.y < e->map.size.y && p.y < 26)
	{
		p.x = -1;
		while (++p.x < e->map.size.x && p.x < 34)
		{
			if (e->map.map[p.y][p.x])
				add_wall(e, p);
		}
	}
	add_player(e);
}
