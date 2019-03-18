/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 11:38:40 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 17:18:04 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"
#include <stdio.h>

int	ft_def_menu_event(int button, int x, int y, t_vars *vars)
{
	int	button_pressed;

	if (x < 0 || x > MENUWINWID || y < 0 || y > MENUWINHEI)
		return (0);
	button_pressed = x / (MENUWINWID / BTN_ROW) + ((y / (MENUWINHEI / BTN_COL)) * BTN_COL);
	printf("PRESSED%d|%d\n", button, button_pressed);
	vars->win_ch[1] = 1;
	if (button_pressed == 0)
	{
		if (button == 1)
			vars->rotx = vars->rotx <= 0 ? 1 : 0;
		if (button == 2)
			vars->rotx = vars->rotx >= 0 ? -1 : 0;
//		if (mlx->rotx)
//			mlx->btns_cols[button_pressed] = mlx->rotx > 0 ? LIGHT_GREEN : RED;
//		else
//			mlx->btns_cols[button_pressed] = BLACK;
	}
	if (button_pressed == 1)
	{
		if (button == 1)
			vars->roty = vars->roty <= 0 ? 1 : 0;
		if (button == 2)
			vars->roty = vars->roty >= 0 ? -1 : 0;
//		if (mlx->roty)
//			mlx->btns_cols[button_pressed] = mlx->roty > 0 ? LIGHT_GREEN : RED;
//		else
//			mlx->btns_cols[button_pressed] = BLACK;
	}
	if (button_pressed == 2)
	{
		if (button == 1)
			vars->rotz = vars->rotz <= 0 ? 1 : 0;
		if (button == 2)
			vars->rotz = vars->rotz >= 0 ? -1 : 0;
//		if (mlx->rotz)
//			mlx->btns_cols[button_pressed] = mlx->rotz > 0 ? LIGHT_GREEN : RED;
//		else
//			mlx->btns_cols[button_pressed] = BLACK;
	}
	if (button_pressed == 4)
	{
		if (button == 1)
			vars->rotspdir = 1;
		if (button == 2)
			vars->rotspdir = -1;
		vars->btns_cols[button_pressed] = vars->rotspdir > 0 ? BLUE : ORANGE;
/*
		if (button == 1)
			mlx->rotspd += (mlx->rotspd > 0.5 ? 0.25 : 0.05);
		if (button == 2 && mlx->rotspd > 0.05)
			mlx->rotspd -= (mlx->rotspd > 0.5  ? 0.25 : 0.05);
*/
	}
	if (button_pressed == 5)
	{
		if (button == 1)
			vars->zoomdir = 1;
		if (button == 2)
			vars->zoomdir = -1;
		vars->btns_cols[button_pressed] = vars->zoomdir > 0 ? BLUE : ORANGE;
		/*
		if (button == 1)
			mlx->zoom += mlx->zoom > 5 ? 1 : 0.1;
		if (button == 2 && mlx->zoom > 0.1)
			mlx->zoom -= mlx->zoom > 5 ? 1 : 0.1;
			*/
	}
	if (button_pressed == 3)
	{
		ft_reset_all(vars);
		vars->win_ch[0] = 1;
	}
	vars->win_ch[1] = 1;
	return (0);
}

int	ft_menu_mouse_event_v2_release(int button, int x, int y, t_vars *vars)
{
	printf("RELEASED%d\n", button);
	vars->rotspdir = 0;
	vars->zoomdir = 0;
	vars->win_ch[1] = 1;
	vars->btns_cols[4] = BLACK;
	vars->btns_cols[5] = BLACK;
	vars->win_ch[1] = 1;
	vars->win_ch[1] = 1;
	return (0);
}


int	ft_menu_mouse_event(int button, int x, int y, t_vars *vars)
{
	ft_def_menu_event(button, x, y, vars);
	return (0);
}
int		ft_bind_events(t_mlx *mlx)
{
	mlx_hook(mlx->mainwin->win, 17, 1L<<17,  ft_exit, mlx);
	mlx_hook(mlx->menuwin->win, 5, 1L<<3, ft_menu_mouse_event_v2_release, mlx->chvars);
	mlx_mouse_hook(mlx->menuwin->win, ft_menu_mouse_event, mlx->chvars);
	return (0);
}

