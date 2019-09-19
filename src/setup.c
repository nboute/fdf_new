/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:44:31 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 15:24:54 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>
#include "../minilibx_macos/mlx.h"

int				scale_point_values(t_mlx *mlx)
{
	int			x;
	int			y;
	int			zrange;
	int			zrange2;

	zrange = mlx->chvars.z[1] - mlx->chvars.z[0];
	zrange2 = (mlx->gridwid + mlx->gridhei) > 16 ?
		(mlx->gridhei + mlx->gridwid) / 12 : (mlx->gridhei + mlx->gridwid) / 4;
	y = 0;
	while (y < mlx->gridhei)
	{
		x = -1;
		while (++x < mlx->gridwid)
		{
			mlx->points[y][x].x -= (double)(mlx->gridwid - 1) / (double)2;
			mlx->points[y][x].y -= (double)(mlx->gridhei - 1) / (double)2;
			mlx->points[y][x].z = ft_dmap(mlx->points[y][x].z -
					mlx->chvars.z[0], zrange, 0, zrange2);
		}
		y++;
	}
	mlx->chvars.z[0] = -zrange2;
	mlx->chvars.z[1] = zrange2;
	return (0);
}

int				init_menu_win(t_mlx *mlx)
{
	mlx->menuwin->wid = MENUWINWID;
	mlx->menuwin->hei = MENUWINHEI;
	if (!(mlx->menuwin->win =
				mlx_new_window(mlx->mlx, MENUWINWID, MENUWINHEI, "Menu")))
		return (0);
	if (mlx->menuwin->img)
		mlx_destroy_image(mlx->mlx, mlx->menuwin->img);
	if (!(mlx->menuwin->img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI)))
		return (0);
	if (!(mlx->menuwin->data =
				mlx_get_data_addr(mlx->menuwin->img, &mlx->menuwin->bpx,
					&mlx->menuwin->size_line, &mlx->menuwin->endian)))
		return (0);
	reset_all(&mlx->chvars);
	mlx_hook(mlx->menuwin->win, 17, 1L << 17, init_menu_win, (void*)mlx);
	mlx_hook(mlx->menuwin->win, 5, 1L << 3, menu_mouse_release_event,
			&mlx->chvars);
	mlx_mouse_hook(mlx->menuwin->win, menu_mouse_event, &mlx->chvars);
	mlx_key_hook(mlx->menuwin->win, menu_key_event, &mlx->chvars);
	return (1);
}

t_mlx			*setup_mlx_p2(t_mlx *mlx)
{
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	if (!(mlx->mainwin = (t_win*)malloc(sizeof(t_win))))
		return (NULL);
	if (!(mlx->menuwin = (t_win*)malloc(sizeof(t_win))))
		return (NULL);
	mlx->menuwin->img = NULL;
	if (!(mlx->mainwin->win =
				mlx_new_window(mlx->mlx, MAINWINWID, MAINWINHEI, "FDF")))
		return (NULL);
	mlx->mainwin->wid = MAINWINWID;
	mlx->mainwin->hei = MAINWINHEI;
	if (!(mlx->mainwin->img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI)))
		return (NULL);
	if (!(mlx->mainwin->data =
				mlx_get_data_addr(mlx->mainwin->img, &mlx->mainwin->bpx,
					&mlx->mainwin->size_line, &mlx->mainwin->endian)))
		return (NULL);
	mlx->chvars.defaultzoom = ((double)500 / (double)mlx->gridwid +
			(double)500 / (double)mlx->gridhei) / (double)2;
	mlx_hook(mlx->mainwin->win, 3, 1L << 1, main_key_release_event,
			&mlx->chvars);
	mlx_hook(mlx->mainwin->win, 2, 1L << 0, main_key_press_event,
			&mlx->chvars);
	mlx_hook(mlx->mainwin->win, 4, 1L << 2, main_mouse_press_event,
			&mlx->chvars);
	mlx_hook(mlx->mainwin->win, 5, 1L << 3, main_mouse_release_event,
			&mlx->chvars);
	return (init_menu_win(mlx) != 0 ? mlx : NULL);
}

t_mlx			*setup_mlx(t_mlx *mlx)
{
	int			i;
	t_fileline	*tmp;

	if (!(mlx->points =
				(t_point**)malloc(sizeof(t_point*) * (mlx->gridhei + 1))))
		return (NULL);
	mlx->points[mlx->gridhei] = NULL;
	i = 0;
	while (i < mlx->gridhei && mlx->lines)
	{
		tmp = mlx->lines;
		mlx->points[i] = mlx->lines->points;
		mlx->lines = mlx->lines->next;
		free(tmp);
		tmp = NULL;
		i++;
	}
	scale_point_values(mlx);
	return (setup_mlx_p2(mlx));
}
