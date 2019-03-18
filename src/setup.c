/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:44:31 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 18:10:02 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>
#include "../minilibx_macos/mlx.h"
#include <stdio.h>

int		ft_scale_point_values(t_mlx *mlx)
{
	int	x;
	int	y;
	int	zrange;
	int	zrange2;

	zrange = mlx->z[1] - mlx->z[0];
	zrange2 = (mlx->gridwid + mlx->gridhei) > 16 ?
		(mlx->gridhei + mlx->gridwid) / 12 : (mlx->gridhei + mlx->gridwid) / 4;
	y = 0;
	while (y < mlx->gridhei)
	{
		x = 0;
		while (x < mlx->gridwid)
		{
			mlx->points[y][x].x -= (double)(mlx->gridwid - 1) / (double)2;
			mlx->points[y][x].y -= (double)(mlx->gridhei - 1) / (double)2;
			mlx->points[y][x].z = ft_dmap(mlx->points[y][x].z - mlx->z[0], zrange, -zrange2, zrange2) ;
			printf("%.1lf ", mlx->points[y][x].x);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("%zu|%zu\n", mlx->gridwid, mlx->gridwid / 2);
	getchar();
	return (0);
}

t_mlx	*ft_setup_mlx_p2(t_mlx *mlx)
{
	int	a;
	int	b;
	int	c;
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	if (!(mlx->mainwin = (t_win*)malloc(sizeof(t_win))))
		return (NULL);
	if (!(mlx->mainwin->win =
				mlx_new_window(mlx->mlx, MAINWINWID, MAINWINHEI, "FDF")))
		return (NULL);
	mlx->mainwin->wid = MAINWINWID;
	mlx->mainwin->hei = MAINWINHEI;
	if (!(mlx->mainwin->img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI)))
		return (NULL);
	if (!(mlx->mainwin->data =
				mlx_get_data_addr(mlx->mainwin->img, &mlx->mainwin->bpx, &mlx->mainwin->size_line, &mlx->mainwin->endian)))
		return (NULL);
	if (!(mlx->menuwin = (t_win*)malloc(sizeof(t_win))))
		return (NULL);
	mlx->menuwin->wid = MENUWINWID;
	mlx->menuwin->hei = MENUWINHEI;
	if (!(mlx->menuwin->win =
				mlx_new_window(mlx->mlx, MENUWINWID, MENUWINHEI, "Menu")))
		return (NULL);
	if (!(mlx->menuwin->img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI)))
		return (NULL);
	if (!(mlx->menuwin->data =
				mlx_get_data_addr(mlx->menuwin->img, &mlx->menuwin->bpx, &mlx->menuwin->size_line, &mlx->menuwin->endian)))
		return (NULL);
	if (!(mlx->chvars = (t_vars*)malloc(sizeof(t_vars))))
		return (NULL);
	mlx->chvars->defaultzoom = ((double)500 / (double)mlx->gridwid +
			(double)500 / (double)mlx->gridhei) / (double)2;
	/*
	mlx->rotx = 0;
	mlx->roty = 0;
	mlx->rotz = 0;
	mlx->rotxval = 0;
	mlx->rotyval = 0;
	mlx->rotzval = 0;
	mlx->rotspd = 0.2;
	mlx->chvars->rotspdir = 0;
	mlx->chvars->zoomdir = 0;*/
	ft_reset_all(mlx->chvars);
	mlx->chvars->win_ch[0] = 1;
	mlx->chvars->win_ch[1] = 0;
	return (mlx);
}

t_mlx	*ft_setup_mlx(t_mlx *mlx)
{
	int	i;
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
	ft_scale_point_values(mlx);
	return (ft_setup_mlx_p2(mlx));
}
