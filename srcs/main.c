/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:52:55 by fwiley            #+#    #+#             */
/*   Updated: 2019/11/08 17:04:46 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			solve(t_figure *figure)
{
	t_figure	*first;
	t_map		map;
	t_border	border;

	get_type(figure);
	first = figure;
	map = get_map();
	border = get_border(get_map_size(figure));
	while (error(map, figure, border))
	{
		border = get_border(border.size + 1);
		reset(figure);
	}
	print_map(figure, border.size);
	free_figures(first);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_figure	*figure;

	figure = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if ((read(fd, argv[1], 0) == 0))
		{
			if ((figure = git_fig(fd, figure, 'A')))
			{
				solve(figure);
				close(fd);
				return (0);
			}
			close(fd);
		}
		ft_putstr("error\n");
		return (0);
	}
	ft_putstr("usage: ./fillit [file]\n");
	return (0);
}
