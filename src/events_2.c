/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 05:53:56 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 06:36:52 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		ft_reset_all(t_vars *vars)
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
	vars->win_ch[0] = 1;
	vars->win_ch[1] = 1;
	vars->color[0] = 255;
	vars->color[1] = 255;
	vars->color[2] = 255;
	vars->color[3] = 255;
	vars->color[4] = 255;
	vars->color[5] = 255;
	vars->select_col = NULL;
	vars->col_start = WHITE;
	vars->col_end = WHITE;
	vars->col_ch = 1;
}

int			ft_change_n_check_vars(t_vars *vars)
{
	if (vars->zoomdir)
		if ((vars->zoomdir != -1 || vars->zoom > 0.05) &&
				(vars->zoom < 1000 || vars->zoomdir == -1))
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
