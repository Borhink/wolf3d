/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:49:57 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/13 18:02:32 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	launch_wolf(t_env *e)
{
	e->view.pos = set_vect2d(1.5, 1.5);
	e->view.dir = set_vect2d(1, 0);
	e->view.plane = set_vect2d(0, 0.66);
	e->key.up = 0;
	e->key.down = 0;
	e->key.right = 0;
	e->key.left = 0;
	e->key.walk = 0;
	e->key.lookdown = 0;
	e->key.lookup = 0;
	e->spd = 0.12;
	e->hgt = 0;
	e->handp = set_vect2i(WIN_W / 2 - e->hand.wth / 2, WIN_H - 100);
	create_textures(e);
	mlx_hook(e->win, KEYPRESS, KEYPRESS_MASK, key_pressed, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASE_MASK, key_released, e);
	mlx_hook(e->win, DESTROYNOTIFY, STRUCTURE_NOTIFY_MASK, window_destroyed, e);
	mlx_loop_hook(e->mlx, apply_event, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}

int			main(void)
{
	t_env	e;

	if (!(e.mlx = mlx_init()))
		ft_putendl("Creation of mlx failed.");
	else if (!(create_map(&(e.map))))
		ft_putendl("Creation of the map failed");
	else if (!(e.win = mlx_new_window(e.mlx, WIN_W, WIN_H, "Wolf3D")))
		ft_putendl("Creation of the window failed.");
	else if (!(create_img(&e, &(e.img))))
		ft_putendl("Creation of the image failed.");
	else
		launch_wolf(&e);
	return (0);
}
