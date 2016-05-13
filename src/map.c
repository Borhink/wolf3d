/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 20:57:17 by qhonore           #+#    #+#             */
/*   Updated: 2016/05/12 15:36:57 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		free_map(t_map *m)
{
	int		y;

	y = -1;
	while (++y < m->size.y)
		if (m->map && m->map[y])
			free(m->map[y]);
	if (m->map)
		free(m->map);
}

static int	get_map_size(int fd, char *line, t_map *m)
{
	int		i;
	char	*chr;

	m->map = NULL;
	if (get_next_line(fd, &line) < 1
		|| !(m->size.y = ft_atoi(line)) || m->size.y > 1000
		|| !(chr = ft_strchr(line, ' '))
		|| !(m->size.x = ft_atoi(chr + 1)) || m->size.x > 1000
		|| !(m->map = (int**)malloc(sizeof(int*) * m->size.y)))
		return (0);
	i = -1;
	while (++i < m->size.y)
		if (!(m->map[i] = (int*)malloc(sizeof(int) * m->size.x)))
			return (0);
	ft_free((void**)(&line));
	return (1);
}

static int	fill_map(t_map *m, int fd, char *line)
{
	t_vect2i	p;
	char		*chr;
	int			ret;

	p.y = -1;
	ret = -1;
	while (++p.y < m->size.y)
	{
		ret = get_next_line(fd, &line);
		p.x = 0;
		m->map[p.y][p.x] = (line ? ft_atoi(line) : 1);
		chr = line;
		while (++p.x < m->size.x)
		{
			if (chr)
				chr = ft_strchr(chr, '\t');
			m->map[p.y][p.x] = chr && *(++chr) ? ft_atoi(chr) : 1;
		}
		ft_free((void**)(&line));
	}
	return (ret < 0 ? 0 : 1);
}

int			create_map(t_map *m)
{
	char		*line;
	int			fd;

	line = NULL;
	if ((fd = open("map.w3d", O_RDONLY)) < 0 || !get_map_size(fd, line, m)
		|| !fill_map(m, fd, line))
	{
		free_map(m);
		return (0);
	}
	close(fd);
	return (1);
}
