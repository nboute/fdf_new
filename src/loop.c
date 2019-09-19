/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:58:44 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 15:13:51 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include "../minilibx_macos/mlx.h"

void		rot_vals(double *x, double *y, double *z, float r[3])
{
	double	tmp;
	double	tmp2;

	tmp = cos(r[1]) * cos(r[2]) * *x - cos(r[1]) * sin(r[2]) * *y +
		sin(r[1]) * *z;
	tmp2 = (sin(r[0]) * sin(r[1]) * cos(r[2]) + cos(r[0]) * sin(r[2])) * *x
		+ (-(sin(r[0]) * sin(r[1]) * sin(r[2])) + cos(r[0]) * cos(r[2])) * *y
		- sin(r[0]) * cos(r[1]) * *z;
	*z = (-cos(r[0]) * sin(r[1] * cos(r[2]) + sin(r[0] * sin(r[2])))) * *x
		+ (cos(r[0]) * sin(r[1]) * sin(r[2]) + sin(r[0]) * cos(r[2])) * *y
		+ cos(r[0]) * cos(r[1]) * *z;
	*x = tmp;
	*y = tmp2;
}

void		get_rots_n_proj(t_vars *vars, float rot[3])
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

void		change_vals(t_point *p, t_vars *vars, float rot[3])
{
	p->rx = p->x * vars->zoom;
	p->ry = p->y * vars->zoom;
	p->rz = p->z * vars->zoom;
	rot_vals(&p->rx, &p->ry, &p->rz, rot);
	p->rx += MAINWINWID / 2 + vars->padx;
	p->ry += MAINWINHEI / 2 + vars->pady;
}

void		reset_rot_draw(t_mlx *mlx, int (*ft)(t_point *a, t_point *b,
			t_win *win))
{
	int		y;
	int		x;
	float	rot[3];

	get_rots_n_proj(&mlx->chvars, rot);
	y = -1;
	while (++y < mlx->gridhei)
	{
		x = -1;
		while (++x < mlx->gridwid)
		{
			change_vals(&mlx->points[y][x], &mlx->chvars, rot);
			if (mlx->chvars.col_ch)
				mlx->points[y][x].color = color_grad(
						mlx->chvars.col_start, mlx->chvars.col_end,
						((mlx->points[y][x].z + mlx->chvars.z[1]) * 100) /
							(mlx->chvars.z[1] * 2));
			if (x > 0)
				ft(&(mlx->points[y][x]),
						&(mlx->points[y][x - 1]), mlx->mainwin);
			if (y > 0)
				ft(&(mlx->points[y][x]),
						&(mlx->points[y - 1][x]), mlx->mainwin);
		}
	}
}

int			loop(t_mlx *mlx)
{
	change_n_check_vars(&mlx->chvars);
	if (mlx->chvars.win_ch[0] != 0)
	{
		mlx_destroy_image(mlx->mlx, mlx->mainwin->img);
		mlx->mainwin->img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI);
		mlx->mainwin->data = mlx_get_data_addr(mlx->mainwin->img,
				&mlx->mainwin->bpx, &mlx->mainwin->size_line,
				&mlx->mainwin->endian);
		reset_rot_draw(mlx,
				mlx->chvars.col_start == mlx->chvars.col_end ?
				draw_line : draw_line_select);
		mlx_put_image_to_window(mlx->mlx, mlx->mainwin->win, mlx->mainwin->img,
			0, 0);
		mlx->chvars.win_ch[0] = 0;
	}
	if (mlx->chvars.win_ch[1])
	{
		mlx_destroy_image(mlx->mlx, mlx->menuwin->img);
		mlx->menuwin->img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI);
		mlx->menuwin->data = mlx_get_data_addr(mlx->menuwin->img,
				&mlx->menuwin->bpx, &mlx->menuwin->size_line,
				&mlx->menuwin->endian);
		draw_default_menu(mlx);
	}
	return (0);
}
