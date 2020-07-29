/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:19:49 by fwiley            #+#    #+#             */
/*   Updated: 2019/11/05 12:07:03 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_map			get_map(void)
{
	t_map		map;
	size_t		i;

	map.top = 0;
	map.bottom = 0;
	i = 0;
	while (i < 20)
	{
		map.last_top[i] = 0;
		map.last_bottom[i] = 0;
		i++;
	}
	return (map);
}

int				get_map_size(t_figure *figure)
{
	int			map_size;
	int			area;
	int			amt_fig;
	t_figure	*tmp;

	tmp = figure;
	amt_fig = 0;
	map_size = 2;
	while (tmp)
	{
		if (tmp->width > map_size)
			map_size = tmp->width;
		if (tmp->height > map_size)
			map_size = tmp->height;
		amt_fig++;
		tmp = tmp->next;
	}
	area = amt_fig * 4;
	while (map_size * map_size < area)
		map_size++;
	return (map_size);
}

t_border		get_border(int border_size)
{
	t_border	border;
	int			i;

	border.size = border_size;
	border_size--;
	border.right = -1;
	border.right >>= border_size;
	border.right = ~border.right;
	i = 0;
	while (i++ < 7)
		border.right = border.right | border.right >> 16;
	border.right = ~border.right;
	border.bottom_2 = -1;
	if (border_size < 8)
	{
		border.bottom_1 = -1;
		border.bottom_1 >>= border_size * 16;
	}
	else
	{
		border.bottom_1 = 0;
		border.bottom_2 >>= (border_size - 8) * 16;
	}
	return (border);
}

void			print_map(t_figure *figure, int map_size)
{
	char		map[257];
	int			i;

	i = 0;
	while (i < 256)
		map[i++] = '.';
	map[256] = '\0';
	while (figure)
	{
		i = 0;
		while ((figure->top || figure->bottom) & (map[i++] != '\0'))
		{
			if (figure->top >> 127)
				map[i - 1] = figure->letter;
			figure->top = figure->bottom >> 127 | figure->top << 1;
			figure->bottom <<= 1;
		}
		figure = figure->next;
	}
	i = 0;
	while (i < map_size)
	{
		write(1, &map[i++ * 16], map_size);
		ft_putchar('\n');
	}
}

void			free_figures(t_figure *figure)
{
	if (figure->next)
		free_figures(figure->next);
	free(figure);
	figure = NULL;
}
