/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:44:49 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 19:41:01 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int		ft_abs(double val)
{
	return (val > 0 ? (int)val : -(int)val);
}

void	ft_place_point(int x, int y, t_mlx *mlx, int color)
{
	//*(unsigned*)(mlx->mainwin->data + ((mlx->mainwin->bpx / 8) * (x + MAINWINWID / 2)) + (mlx->mainwin->size_line * (y + MAINWINHEI / 2))) = color;
	*(unsigned*)(mlx->mainwin->data + ((mlx->mainwin->bpx / 8) * (x)) + (mlx->mainwin->size_line * (y))) = color;
}

int	ft_set_values(int x[2], int y[2], int delta[2], int sign[2])
{
	delta[0] = labs(x[0] - x[1]);
	delta[1] = labs(y[0] - y[1]);
	sign[0] = x[0] < x[1] ? 1 : -1;
	sign[1] = y[0] < y[1] ? 1 : -1;
	return (delta[0] > delta[1] ? delta[0] / 2 : -delta[1] / 2);
}

void	ft_set_points(int x[2], int y[2], t_point *a, t_point *b)
{
	x[0] = (int)a->rx;
	x[1] = (int)b->rx;
	y[0] = (int)a->ry;
	y[1] = (int)b->ry;
}

int		ft_draw_line_grad(t_point *a, t_point *b, t_mlx *mlx)
{
//	double x[2];
//	double	y[2];
	int	x[2];
	int	y[2];
	int	delta[2];
	int	diff[2];
	int	sign[2];

	ft_set_points(x, y, a, b);
	diff[0] = ft_set_values(x, y, delta, sign);
	
	//	printf("Ba|%d|%d|%d|%d\n", x[0], x[1], y[0], y[1]);
//		getchar();
	while (1)
	{
		if (x[0] > 0 && x[0] < MAINWINWID && y[0] > 0 && y[0] < MAINWINHEI)
			ft_place_point(x[0], y[0], mlx, 0x00FFFFFF);
		if (x[0] == x[1] && y[0] == y[1])
			return (0);
		diff[1] = diff[0];
		if (diff[1] > -delta[0])
			diff[0] -= delta[1];
		if (diff[1] > -delta[0])
			x[0] += sign[0];
		if (diff[1] < delta[1])
			diff[0] += delta[0];
		if (diff[1] < delta[1])
			y[0] += sign[1];
//		printf("X:%d|Y:%d|DIFF1:%d|DIFF0:%d|DELTA[0]:%d|DELTA[1]:%d\n", x[0], y[0], diff[1], diff[0], delta[0], delta[1]);
//		getchar();
	}
}

int		ft_draw_line(t_point *a, t_point *b, t_mlx *mlx)
{
//	double x[2];
//	double	y[2];
	int	x[2];
	int	y[2];
	int	delta[2];
	int	diff[2];
	int	sign[2];

	ft_set_points(x, y, a, b);
	diff[0] = ft_set_values(x, y, delta, sign);
	
	//	printf("Ba|%d|%d|%d|%d\n", x[0], x[1], y[0], y[1]);
//		getchar();
	while (1)
	{
		if (x[0] > 0 && x[0] < MAINWINWID && y[0] > 0 && y[0] < MAINWINHEI)
		ft_place_point(x[0], y[0], mlx, 0x00FFFFFF);
		if (x[0] == x[1] && y[0] == y[1])
			return (0);
		diff[1] = diff[0];
		if (diff[1] > -delta[0])
			diff[0] -= delta[1];
		if (diff[1] > -delta[0])
			x[0] += sign[0];
		if (diff[1] < delta[1])
			diff[0] += delta[0];
		if (diff[1] < delta[1])
			y[0] += sign[1];
//		printf("X:%d|Y:%d|DIFF1:%d|DIFF0:%d|DELTA[0]:%d|DELTA[1]:%d\n", x[0], y[0], diff[1], diff[0], delta[0], delta[1]);
//		getchar();
	}
}
/*
int		ft_draw_line(t_point *a, t_point *b, t_mlx *mlx)
{
	double	dx;
	double	dy;
	int	 steps;
	double	dirx;
	double	diry;

	dx = b->rx - a->rx;
	dy = b->ry - a->ry;
	if (ft_abs(dx) > ft_abs(dy))
	{
		steps = ft_abs(dx);
		dirx = dx > 0 ? 1 : -1;
		diry = dy / steps;
	}
	else
	{
		steps = ft_abs(dy);
		diry = dy > 0 ? 1 : -1;
		dirx = dx / steps;
	}
	int	i;
	i = 0;
	double x;
	double y;
	x = a->rx;
	y = a->ry;
//	printf("%lf|%lf|%lf|%lf|%lf|%lf|%d\n", x, b->rx, y, b->ry, dirx, diry, steps);
	while (i < steps)
	{
		int tmp;
		tmp = lround(x);
		x = x + dirx;
		y = y + diry;
	if ((lround(x) + MAINWINWID / 2) < MAINWINWID && (lround(x) + MAINWINWID / 2) > 0 && (lround(y) + MAINWINHEI / 2) < MAINWINHEI && (lround(y) + MAINWINHEI / 2) > 0)
		ft_place_point(lround(x), lround(y), mlx, 0x00FFFFFF);
		i++;
	}
	return (0);
}
*/
void	ft_draw_grad(t_mlx *mlx)
{
	int	x;
	int	y;
//	int	ver;
//	int	very;

	y = 0;
	while (y < mlx->gridhei)
	{
		x = 0;
		while (x < mlx->gridwid)
		{
			if (x + 1 < mlx->gridwid)
				ft_draw_line_grad(&(mlx->points[y][x]), &(mlx->points[y][x + 1]), mlx);
			if (y + 1 < mlx->gridhei)
				ft_draw_line_grad(&(mlx->points[y][x]), &(mlx->points[y + 1][x]), mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mainwin->win, mlx->mainwin->img, 0, 0);
}
void	ft_draw(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->gridhei)
	{
		x = 0;
		while (x < mlx->gridwid)
		{
			if (x + 1 < mlx->gridwid)
				ft_draw_line(&(mlx->points[y][x]), &(mlx->points[y][x + 1]), mlx);
			if (y + 1 < mlx->gridhei)
				ft_draw_line(&(mlx->points[y][x]), &(mlx->points[y + 1][x]), mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mainwin->win, mlx->mainwin->img, 0, 0);
}
/*
void	ft_select_draw_type(t_mlx *mlx)
{
	if (mlx->chvars->colstart == mlx->chvars->colend)
	{
	}
	
}*/
