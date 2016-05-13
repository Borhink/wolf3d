/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 22:27:54 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/13 18:03:48 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	free_datas_and_quit(t_env *e)
{
	free_map(&(e->map));
	mlx_destroy_image(e->mlx, e->img.i);
	mlx_destroy_image(e->mlx, e->hand.i);
	mlx_destroy_image(e->mlx, e->t[0].i);
	mlx_destroy_image(e->mlx, e->t[1].i);
	mlx_destroy_image(e->mlx, e->t[2].i);
	mlx_destroy_image(e->mlx, e->t[3].i);
	mlx_destroy_image(e->mlx, e->t[4].i);
	mlx_destroy_window(e->mlx, e->win);
	exit(1);
}

int			window_destroyed(void *env)
{
	t_env *e;

	e = (t_env*)env;
	free_datas_and_quit(e);
	return (1);
}

int			key_pressed(int key, void *env)
{
	t_env *e;

	e = (t_env*)env;
	if (key == 53)
		free_datas_and_quit(e);
	if (key == 6)
		e->key.walk = 1;
	if (key == 7)
		e->key.lookdown = 1;
	if (key == 8)
		e->key.lookup = 1;
	if (key == 126)
		e->key.up = 1;
	if (key == 125)
		e->key.down = 1;
	if (key == 123)
		e->key.left = 1;
	if (key == 124)
		e->key.right = 1;
	return (1);
}

int			key_released(int key, void *env)
{
	t_env *e;

	e = (t_env*)env;
	if (key == 6)
		e->key.walk = 0;
	if (key == 7)
		e->key.lookdown = 0;
	if (key == 8)
		e->key.lookup = 0;
	if (key == 126)
		e->key.up = 0;
	if (key == 125)
		e->key.down = 0;
	if (key == 123)
		e->key.left = 0;
	if (key == 124)
		e->key.right = 0;
	return (1);
}
