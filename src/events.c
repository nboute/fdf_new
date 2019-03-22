/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 11:38:40 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 05:46:14 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"

void	ft_def_menu_event_p1(int button, int button_pressed, t_vars *vars)
{
	if (button_pressed == 0)
	{
		if (button == 1)
			vars->rotx = vars->rotx <= 0 ? 1 : 0;
		if (button == 2)
			vars->rotx = vars->rotx >= 0 ? -1 : 0;
	}
	if (button_pressed == 1)
	{
		if (button == 1)
			vars->roty = vars->roty <= 0 ? 1 : 0;
		if (button == 2)
			vars->roty = vars->roty >= 0 ? -1 : 0;
	}
	if (button_pressed == 2)
	{
		if (button == 1)
			vars->rotz = vars->rotz <= 0 ? 1 : 0;
		if (button == 2)
			vars->rotz = vars->rotz >= 0 ? -1 : 0;
	}
	if (button_pressed == 3)
		ft_reset_all(vars);
	if (button_pressed == 3)
		vars->win_ch[0] = 1;
}

void	ft_def_menu_event_p2(int button, int button_pressed, t_vars *vars)
{
	if (button_pressed == 4)
	{
		if (button == 1)
			vars->rotspdir = 1;
		if (button == 2)
			vars->rotspdir = -1;
		vars->btns_cols[button_pressed] = vars->rotspdir > 0 ? BLUE : ORANGE;
	}
	if (button_pressed == 5)
	{
		if (button == 1)
			vars->zoomdir = 1;
		if (button == 2)
			vars->zoomdir = -1;
		vars->btns_cols[button_pressed] = vars->zoomdir > 0 ? BLUE : ORANGE;
	}
}

int		ft_menu_mouse_event(int button, int x, int y, t_vars *vars)
{
	int	button_pressed;

	if (x < 0 || x > MENUWINWID || y < 0 || y > MENUWINHEI)
		return (0);
	button_pressed = x / (MENUWINWID / BTN_ROW) +
		((y / (MENUWINHEI / BTN_COL)) * BTN_COL);
	vars->win_ch[1] = 1;
	if (button_pressed >= 0 && button_pressed <= 3)
		ft_def_menu_event_p1(button, button_pressed, vars);
	if (button_pressed == 4 || button_pressed == 5)
		ft_def_menu_event_p2(button, button_pressed, vars);
	if (button == 1 || button == 2)
	{
		if (button_pressed == 6)
			vars->select_col = button == 1 ? &vars->color[0] : &vars->color[3];
		if (button_pressed == 7)
			vars->select_col = button == 1 ? &vars->color[1] : &vars->color[4];
		if (button_pressed == 8)
			vars->select_col = button == 1 ? &vars->color[2] : &vars->color[5];
		if (button_pressed >= 6 && button_pressed <= 8)
			vars->btns_cols[button_pressed] = DARK_GREEN;
	}
	return (0);
}

int		ft_menu_key_event(int keycode, t_vars *vars)
{
	int	val;

	if (!vars->select_col)
		return (1);
	if (keycode == 36 || keycode == 76)
	{
		vars->col_start =
			(vars->color[0] << 16) + (vars->color[1] << 8) + vars->color[2];
		vars->col_end =
			(vars->color[3] << 16) + (vars->color[4] << 8) + vars->color[5];
		vars->btns_cols[6] = BLACK;
		vars->btns_cols[7] = BLACK;
		vars->btns_cols[8] = BLACK;
		vars->win_ch[0] = 1;
		vars->win_ch[1] = 1;
	}
	if (keycode >= 82 && keycode <= 92 && keycode != 90)
	{
		val = keycode >= 91 ? keycode - 83 : keycode - 82;
		if (*vars->select_col % 100 > 29)
			*vars->select_col = *vars->select_col % 10 + 20;
		*vars->select_col = (*vars->select_col % 100) * 10 + val;
		vars->win_ch[1] = 1;
	}
	return (0);
}

int		ft_menu_mouse_release_event(int button, int x, int y, t_vars *vars)
{
	x = 0;
	y = 0;
	button = 0;
	vars->rotspdir = 0;
	vars->zoomdir = 0;
	vars->win_ch[1] = 1;
	vars->btns_cols[4] = BLACK;
	vars->btns_cols[5] = BLACK;
	vars->win_ch[1] = 1;
	vars->win_ch[1] = 1;
	return (0);
}
