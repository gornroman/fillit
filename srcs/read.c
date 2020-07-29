/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:23:13 by fwiley            #+#    #+#             */
/*   Updated: 2019/11/05 16:32:02 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_figure			*git_fig(int fd, t_figure *figure, char letter)
{
	char			c;

	figure = (t_figure *)malloc(sizeof(t_figure));
	if (!figure || letter > 90)
		return (NULL);
	if (!(figure->top = get_nbr(fd, figure)))
	{
		free(figure);
		figure = NULL;
		return (NULL);
	}
	figure->bottom = 0;
	figure->start_top = figure->top;
	figure->start_bottom = 0;
	figure->letter = letter;
	figure->type = 0;
	figure->next = NULL;
	if (read(fd, &c, 1))
		if (c != '\n' ||
		!(figure->next = git_fig(fd, figure->next, letter + 1)))
		{
			free(figure);
			figure = NULL;
		}
	return (figure);
}

__uint128_t			get_nbr(int fd, t_figure *figure)
{
	__uint128_t		nbr;
	char			c;
	int				i;

	nbr = 0;
	i = 0;
	while (i++ < 20)
	{
		if (!(read(fd, &c, 1)))
			return (0);
		if (i % 5)
		{
			if (c != '.' && c != '#')
				return (0);
			nbr <<= 1;
			if (c == '#')
				nbr++;
		}
		else if (c != '\n')
			return (0);
	}
	return (validation(nbr, figure));
}

__uint128_t			get_figure_top(__uint128_t nbr, t_figure *figure)
{
	t_border	mask;

	mask = get_border(5);
	mask.right = mask.right >> 1 | mask.right << 127;
	nbr = ((nbr >> 12) << 124) | (((nbr >> 8) << 124) >> 16)
		| (((nbr >> 4) << 124) >> 32) | ((nbr << 124) >> 48);
	while (!(nbr >> 112))
		nbr <<= 16;
	while (!(nbr & mask.right))
		nbr <<= 1;
	figure->height = 0;
	while ((nbr << (16 * figure->height)))
		figure->height++;
	figure->width = 4;
	mask = get_border(figure->width);
	while (!(mask.right & nbr))
	{
		figure->width--;
		mask = get_border(figure->width);
	}
	return (nbr);
}

__uint128_t			validation(__uint128_t nbr, t_figure *figure)
{
	int				count;
	int				connect;
	int				i;

	count = 0;
	connect = 0;
	i = 0;
	while (i < 16)
	{
		if ((nbr << (i + 112)) >> 127)
		{
			if (i / 4 == (i - 1) / 4)
				connect += nbr << (i + 111) >> 127;
			if (i / 4 == (i + 1) / 4)
				connect += nbr << (i + 113) >> 127;
			connect += nbr << (i + 108) >> 127;
			connect += nbr << (i + 116) >> 127;
			count++;
		}
		i++;
	}
	if ((count == 4) && (connect == 6 || connect == 8))
		return (get_figure_top(nbr, figure));
	return (0);
}

void				get_type(t_figure *figure)
{
	size_t			max;
	t_figure		*tmp;

	if (figure)
	{
		get_type(figure->next);
		tmp = figure->next;
		max = 0;
		while (!figure->type && tmp)
		{
			if (tmp->top == figure->top)
				figure->type = tmp->type;
			if (tmp->type > max)
				max = tmp->type;
			tmp = tmp->next;
		}
		if (!figure->type)
			figure->type = max + 1;
	}
}
