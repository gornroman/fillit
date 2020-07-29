/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:17:46 by fwiley            #+#    #+#             */
/*   Updated: 2019/11/08 17:03:31 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

size_t		error(t_map map, t_figure *figure, t_border border)
{
	size_t	next_fig;

	if (!figure)
		return (0);
	if (find_position(map, figure, border))
	{
		map.last_top[figure->type] = figure->top;
		map.last_bottom[figure->type] = figure->bottom;
		while ((next_fig = error(new_map(map, figure), figure->next, border)))
		{
			if (next_fig == figure->type)
				return (figure->type);
			if (!(shift(figure, border)))
				return (-1);
			map.last_top[figure->type] = figure->top;
			map.last_bottom[figure->type] = figure->bottom;
			if (!find_position(map, figure, border))
				return (-1);
			map.last_top[figure->type] = figure->top;
			map.last_bottom[figure->type] = figure->bottom;
			reset(figure->next);
		}
		return (0);
	}
	return (figure->type);
}

int			find_position(t_map map, t_figure *figure, t_border border)
{
	if (map.last_top[figure->type] || map.last_bottom[figure->type])
	{
		figure->top = map.last_top[figure->type];
		figure->bottom = map.last_bottom[figure->type];
	}
	while ((map.top & figure->top) | (map.bottom & figure->bottom))
	{
		if (!(shift(figure, border)))
			return (0);
	}
	return (1);
}

int			shift(t_figure *figure, t_border border)
{
	if ((figure->top | figure->bottom) & border.right)
	{
		if ((figure->top & border.bottom_1)
			| (figure->bottom & border.bottom_2))
			return (0);
		figure->bottom = figure->bottom >> (16 - border.size + figure->width)
			| (figure->top << (112 + border.size - figure->width));
		figure->top >>= 16 - border.size + figure->width;
		return (1);
	}
	figure->bottom = figure->bottom >> 1 | figure->top << 127;
	figure->top >>= 1;
	return (1);
}

void		reset(t_figure *figure)
{
	if (figure->next)
		reset(figure->next);
	figure->top = figure->start_top;
	figure->bottom = figure->start_bottom;
}

t_map		new_map(t_map map, t_figure *figure)
{
	map.top |= figure->top;
	map.bottom |= figure->bottom;
	return (map);
}
