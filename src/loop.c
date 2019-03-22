/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:58:44 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 05:53:50 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include "../minilibx_macos/mlx.h"

void		ft_get_rots(t_vars *vars, float rot[3])
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

void		ft_change_vals(t_point *p, double zoom, float rot[3])
{
	int		tmp;

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

void		ft_reset_nrot_vals(t_mlx *mlx, int (*ft)(t_point *a, t_point *b,
			t_win *win))
{
	int		y;
	int		x;
	float	rot[3];

	ft_get_rots(mlx->chvars, rot);
	y = -1;
	while (++y < mlx->gridhei)
	{
		x = -1;
		while (++x < mlx->gridwid)
		{
			ft_change_vals(&mlx->points[y][x], mlx->chvars->zoom, rot);
			if (mlx->chvars->col_ch)
				mlx->points[y][x].color = ft_color_grad(
						mlx->chvars->col_start, mlx->chvars->col_end,
						((mlx->points[y][x].z + mlx->chvars->z[1]) * 100) /
							(mlx->chvars->z[1] * 2));
			if (x > 0)
				ft(&(mlx->points[y][x]),
						&(mlx->points[y][x - 1]), mlx->mainwin);
			if (y > 0)
				ft(&(mlx->points[y][x]),
						&(mlx->points[y - 1][x]), mlx->mainwin);
		}
	}
}

void		ft_rotate_point(t_point *p, float xrot, float yrot, float zrot)
{
	int		tmp;

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

int			ft_loop(t_mlx *mlx)
{
	ft_change_n_check_vars(mlx->chvars);
	if (mlx->chvars->win_ch[0] != 0)
	{
		mlx_destroy_image(mlx->mlx, mlx->mainwin->img);
		mlx->mainwin->img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI);
		mlx->mainwin->data = mlx_get_data_addr(mlx->mainwin->img,
				&mlx->mainwin->bpx, &mlx->mainwin->size_line,
				&mlx->mainwin->endian);
		ft_reset_nrot_vals(mlx,
				mlx->chvars->col_start == mlx->chvars->col_end ?
				ft_draw_line : ft_draw_line_select);
		mlx_put_image_to_window(mlx->mlx, mlx->mainwin->win, mlx->mainwin->img,
			0, 0);
		mlx->chvars->win_ch[0] = 0;
	}
	if (mlx->chvars->win_ch[1])
	{
		mlx_destroy_image(mlx->mlx, mlx->menuwin->img);
		mlx->menuwin->img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI);
		mlx->menuwin->data = mlx_get_data_addr(mlx->menuwin->img,
				&mlx->menuwin->bpx, &mlx->menuwin->size_line,
				&mlx->menuwin->endian);
		ft_draw_default_menu(mlx);
	}
	return (0);
}
