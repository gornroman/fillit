/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwiley <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:17:38 by fwiley            #+#    #+#             */
/*   Updated: 2019/11/05 12:56:02 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct		s_figure
{
	__uint128_t		top;
	__uint128_t		bottom;
	__uint128_t		start_top;
	__uint128_t		start_bottom;
	size_t			type;
	int				width;
	int				height;
	char			letter;
	struct s_figure	*next;
}					t_figure;

typedef struct		s_map
{
	__uint128_t		top;
	__uint128_t		bottom;
	__uint128_t		last_top[20];
	__uint128_t		last_bottom[20];
}					t_map;

typedef struct		s_border
{
	int				size;
	__uint128_t		right;
	__uint128_t		bottom_1;
	__uint128_t		bottom_2;
}					t_border;

t_map				new_map(t_map map, t_figure *figure);
void				reset(t_figure *figure);
int					shift(t_figure *figure, t_border border);
int					find_position(t_map map, t_figure *figure, t_border border);
size_t				error(t_map map, t_figure *figure, t_border border);
t_map				get_map(void);
int					get_map_size(t_figure *figure);
t_border			get_border(int border_size);
void				print_map(t_figure *figure, int map_size);
void				free_figures(t_figure *figure);
t_figure			*git_fig(int fd, t_figure *figure, char letter);
__uint128_t			get_nbr(int fd, t_figure *figure);
__uint128_t			get_figure_top(__uint128_t nbr, t_figure *figure);
__uint128_t			validation(__uint128_t nbr, t_figure *figure);
void				get_type(t_figure *figure);
void				solve(t_figure *figure);

#endif
