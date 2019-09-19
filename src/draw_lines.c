/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:44:49 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 15:08:21 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"
#include <stdlib.h>

int		set_values(int xy[4], int delta[4], int sign[2])
{
	delta[0] = ft_abs(xy[0] - xy[1]);
	delta[1] = ft_abs(xy[2] - xy[3]);
	sign[0] = xy[0] < xy[1] ? 1 : -1;
	sign[1] = xy[2] < xy[3] ? 1 : -1;
	delta[2] = 0;
	delta[3] = ft_max_2(delta[0], delta[1]);
	delta[3] = ft_max_2(ft_max_2(delta[0], delta[1]), 1);
	return (delta[0] > delta[1] ? delta[0] / 2 : -delta[1] / 2);
}

void	set_points(int xy[4], t_point *a, t_point *b)
{
	xy[0] = (int)a->rx;
	xy[1] = (int)b->rx;
	xy[2] = (int)a->ry;
	xy[3] = (int)b->ry;
}

int		draw_line_grad(t_point *a, t_point *b, t_win *win)
{
	int	xy[4];
	int	delta[4];
	int	diff[2];
	int	sign[2];

	set_points(xy, a, b);
	diff[0] = set_values(xy, delta, sign);
	while (1)
	{
		if (xy[0] > 0 && xy[0] < MAINWINWID && xy[2] > 0 && xy[2] < MAINWINHEI)
			*(int*)(win->data + ((win->bpx / 8) * (xy[0])) +
					(win->size_line * (xy[2]))) = color_grad(a->color,
						b->color, (delta[2]++ * 100) / delta[3]);
		if (xy[0] == xy[1] && xy[2] == xy[3])
			return (0);
		diff[1] = diff[0];
		if (diff[1] > -delta[0])
			diff[0] -= delta[1];
		if (diff[1] > -delta[0])
			xy[0] += sign[0];
		if (diff[1] < delta[1])
			diff[0] += delta[0];
		if (diff[1] < delta[1])
			xy[2] += sign[1];
	}
}

int		draw_line(t_point *a, t_point *b, t_win *win)
{
	int	xy[4];
	int	delta[4];
	int	diff[2];
	int	sign[2];

	set_points(xy, a, b);
	diff[0] = set_values(xy, delta, sign);
	while (1)
	{
		if (xy[0] > 0 && xy[0] < MAINWINWID && xy[2] > 0 && xy[2] < MAINWINHEI)
			*(unsigned*)(win->data + ((win->bpx / 8) * (xy[0])) +
					(win->size_line * (xy[2]))) = a->color;
		if (xy[0] == xy[1] && xy[2] == xy[3])
			return (0);
		diff[1] = diff[0];
		if (diff[1] > -delta[0])
			diff[0] -= delta[1];
		if (diff[1] > -delta[0])
			xy[0] += sign[0];
		if (diff[1] < delta[1])
			diff[0] += delta[0];
		if (diff[1] < delta[1])
			xy[2] += sign[1];
	}
}

int		draw_line_select(t_point *a, t_point *b, t_win *win)
{
	if (((int)a->rx >= 0 && (int)a->rx < MAINWINWID) ||
			((int)a->ry >= 0 && (int)a->ry < MAINWINHEI))
	{
		if (a->color != b->color)
			draw_line_grad(a, b, win);
		else
			draw_line(a, b, win);
	}
	return (0);
}
