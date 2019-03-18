/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:58:44 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 19:21:12 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include "../minilibx_macos/mlx.h"
#include <stdio.h>

void	ft_get_rots(t_vars *vars, float rot[3])
{
	vars->rotxval += (float)vars->rotx * vars->rotspd;
	vars->rotyval += (float)vars->roty * vars->rotspd;
	vars->rotzval += (float)vars->rotz * vars->rotspd;
	if (vars->rotxval >= (float)360)
		vars->rotxval -= 360;
	if (vars->rotyval >= (float)360)
		vars->rotyval -= 360;
	if (vars->rotzval >= (float)360)
		vars->rotzval -= 360;
	rot[0] = (vars->rotxval * M_PI) / 180;
	rot[1] = (vars->rotyval * M_PI) / 180;
	rot[2] = (vars->rotzval * M_PI) / 180;
}

void	ft_change_vals(t_point *p, int zoom, float rot[3])
{
	int	tmp;

	p->rx = p->x * zoom;
	p->ry = p->y * zoom;
	p->rz = p->z * zoom;
	if (rot[0])
	{
		tmp = cos(rot[0]) * p->ry - sin(rot[0]) * p->rz;
		p->rz = sin(rot[0]) * p->ry + cos(rot[0]) * p->rz;
		p->ry = tmp;
	}
	if (rot[1])
	{
		tmp = cos(rot[1]) * p->rx + sin(rot[1]) * p->rz;
		p->rz = -sin(rot[1]) * p->rx + cos(rot[1]) * p->rz;
		p->rx = tmp;
	}
	if (rot[2])
	{
		tmp = cos(rot[2]) * p->rx - sin(rot[2]) * p->ry;
		p->ry = sin(rot[2]) * p->rx + cos(rot[2]) * p->ry;
		p->rx = tmp;
	}
	p->rx += MAINWINWID / 2;
	p->ry += MAINWINHEI / 2;
}

int		ft_reset_nrot_vals(t_mlx *mlx)
{
	int	i;
	int	j;
	int	zoom;
	float	rot[3];

	ft_get_rots(mlx->chvars, rot);
	zoom = mlx->chvars->zoom;
	i = 0;
	while (i < mlx->gridhei)
	{
		j = 0;
		while (j < mlx->gridwid)
		{
			ft_change_vals(&mlx->points[i][j], zoom, rot);
			/*
			mlx->points[i][j].rx = mlx->points[i][j].x * zoom;
			mlx->points[i][j].ry = mlx->points[i][j].y * zoom;
			mlx->points[i][j].rz = mlx->points[i][j].z * zoom;
			*/
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_rotate_point(t_point *p, float xrot, float yrot, float zrot)
{
	int tmp;
	if (xrot)
	{
		tmp = cos(xrot) * p->ry - sin(xrot) * p->rz;
		p->rz = sin(xrot) * p->ry + cos(xrot) * p->rz;
		p->ry = tmp;
	}
	if (yrot)
	{
		tmp = cos(yrot) * p->rx + sin(yrot) * p->rz;
		p->rz = -sin(yrot) * p->rx + cos(yrot) * p->rz;
		p->rx = tmp;
	}
	if (zrot)
	{
		tmp = cos(zrot) * p->rx - sin(zrot) * p->ry;
		p->ry = sin(zrot) * p->rx + cos(zrot) * p->ry;
		p->rx = tmp;
	}
}

void	ft_reset_all(t_vars *vars)
{
	vars->rotx = 0;
	vars->roty = 0;
	vars->rotz = 0;
	vars->zoom = vars->defaultzoom;
	vars->rotxval = 0;
	vars->rotyval = 0;
	vars->rotzval = 0;
	vars->rotspd = 0.2;
	vars->rotspdir = 0;
	vars->zoomdir = 0;
	//	vars->colstart = WHITE;
	//	vars->colEND = WHITE;
}

#include <stdio.h>
/*
void	ft_rotate(t_mlx *mlx, t_vars *vars)
{
	int	y;
	int	x;
	float xrot;
	float yrot;
	float zrot;

		y = 0;
		vars->rotxval += (float)vars->rotx * vars->rotspd;
		vars->rotyval += (float)vars->roty * vars->rotspd;
		vars->rotzval += (float)vars->rotz * vars->rotspd;
		if (vars->rotxval >= (float)360)
			vars->rotxval -= 360;
		if (vars->rotyval >= (float)360)
			vars->rotyval -= 360;
		if (vars->rotzval >= (float)360)
			vars->rotzval -= 360;
		xrot = (vars->rotxval * M_PI) / 180;
		yrot = (vars->rotyval * M_PI) / 180;
		zrot = (vars->rotzval * M_PI) / 180;
		while (y < mlx->gridhei)
		{
			x = 0;
			while (x < mlx->gridwid)
			{
				if (xrot || yrot || zrot)
					ft_rotate_point(&(mlx->points[y][x]), xrot, yrot, zrot);
				mlx->points[y][x].rx += MAINWINWID / 2;
				mlx->points[y][x].ry += MAINWINHEI / 2;
				x++;
			}
			y++;
		}
}
*/
int		ft_change_n_check_vars(t_vars *vars)
{
	if (vars->zoomdir)
		if (vars->zoomdir != -1 || vars->zoom > 0.01)
		{
			vars->zoom += vars->zoom > 5 ? 0.25 * vars->zoomdir 
				: 0.05 * vars->zoomdir;
			vars->win_ch[0] = 1;
		}
	if (vars->rotspdir)
		if (vars->rotspdir != -1 || vars->rotspd > 0.005)
		{
			vars->rotspd += vars->rotspd > 0.005 ? 0.025 * vars->rotspdir
				: 0.005 * vars->rotspdir;
			if (vars->rotspd > 360)
				vars->rotspd -= 360;
			vars->win_ch[0] = 1;
		}
	if (vars->rotx || vars->roty || vars->rotz)
		vars->win_ch[0] = 1;
	return (0);
}

int		ft_check_change(t_vars *vars)
{
	return (0);
}

int		ft_loop(t_mlx *mlx)
{
	printf("A\n");
	ft_change_n_check_vars(mlx->chvars);
	printf("B\n");
	if (mlx->chvars->win_ch[0] != 0)
	{
	printf("BA\n");
		mlx_destroy_image(mlx->mlx, mlx->mainwin->img);
		mlx->mainwin->img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI);
		mlx->mainwin->data = mlx_get_data_addr(mlx->mainwin->img,
				&mlx->mainwin->bpx, &mlx->mainwin->size_line,
				&mlx->mainwin->endian);
	printf("BB\n");
		ft_reset_nrot_vals(mlx);
	printf("BC\n");
//		ft_rotate(mlx, mlx->chvars);
	printf("BD\n");
		ft_draw(mlx);
	printf("BE\n");
		mlx->chvars->win_ch[0] = 0;
	}
	printf("C\n");
	if (mlx->chvars->win_ch[1])
	{
		mlx_destroy_image(mlx->mlx, mlx->menuwin->img);
		mlx->menuwin->img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI);
		mlx->menuwin->data = mlx_get_data_addr(mlx->menuwin->img,
				&mlx->menuwin->bpx, &mlx->menuwin->size_line, &mlx->menuwin->endian);
	printf("CA\n");
		ft_draw_default_menu(mlx);
	printf("CB\n");
	}
	printf("D\n");
	return (0);
}
