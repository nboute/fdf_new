/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:44:40 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 15:16:17 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/header.h"
#include <stdlib.h>

void	draw_buttons(t_mlx *mlx, t_win *win)
{
	int	x;
	int	y;
	int	curr_btn;

	y = 0;
	x = 0;
	while (y < win->hei)
	{
		x = 0;
		while (x < win->wid)
		{
			curr_btn = (x * BTN_ROW) / win->wid +
				BTN_COL * ((BTN_COL * y) / (win->hei));
			if ((x % (win->wid / BTN_COL)) == 0 ||
					(y % (win->hei / BTN_ROW) == 0))
				*(unsigned*)(win->data + ((win->bpx / 8) * x) +
						(win->size_line) * y) = WHITE;
			else
				*(unsigned*)(win->data + ((win->bpx / 8) * x) + (win->size_line)
						* y) = mlx->chvars.btns_cols[curr_btn];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, win->win, win->img, 0, 0);
}

void	draw_color_val(int btn, t_mlx *mlx, int buthei, int xpos)
{
	char	*tmp;

	tmp = ft_itoa(mlx->chvars.color[btn - 6]);
	if (!tmp)
		ft_exit(3);
	mlx_string_put(mlx->mlx, mlx->menuwin->win, xpos,
			((btn / BTN_COL) * buthei + buthei / 6)
			, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = ft_itoa(mlx->chvars.color[btn - 3]);
	if (!tmp)
		ft_exit(3);
	mlx_string_put(mlx->mlx, mlx->menuwin->win, xpos,
			((btn / BTN_COL) * buthei + (4 * buthei) / 6)
			, 0x00FFFFFF, tmp);
	free(tmp);
}

void	draw_btns_names(t_mlx *mlx, t_win *win)
{
	int	i;
	int	buthei;
	int	butwid;

	i = 0;
	butwid = win->wid / BTN_ROW;
	buthei = win->hei / BTN_COL;
	while (i < BUTTONS)
	{
		mlx_string_put(mlx->mlx, win->win, ((i % BTN_ROW) * butwid + butwid / 2
					- ft_strlen(mlx->chvars.btns_txt[i]) * 5),
				((i / BTN_COL) * buthei + (6 * buthei) / (BTN_COL * 5))
				, 0x00FFFFFF, mlx->chvars.btns_txt[i]);
		if (i >= 6)
			draw_color_val(i, mlx, buthei,
					((i % BTN_ROW) * butwid + butwid / 2) - (butwid / 32) * 3);
		i++;
	}
}

void	determine_buttons_colors(t_vars *vars)
{
	if (vars->rotx)
		vars->btns_cols[0] = vars->rotx > 0 ? LIGHT_GREEN : RED;
	else
		vars->btns_cols[0] = BLACK;
	if (vars->roty)
		vars->btns_cols[1] = vars->roty > 0 ? LIGHT_GREEN : RED;
	else
		vars->btns_cols[1] = BLACK;
	if (vars->rotz)
		vars->btns_cols[2] = vars->rotz > 0 ? LIGHT_GREEN : RED;
	else
		vars->btns_cols[2] = BLACK;
	vars->btns_cols[6] = BLACK;
	vars->btns_cols[7] = BLACK;
	vars->btns_cols[8] = BLACK;
	if (vars->slc_col >= 0)
		vars->btns_cols[(vars->slc_col % 3) + 6] = DARK_GREEN;
}

void	draw_default_menu(t_mlx *mlx)
{
	determine_buttons_colors(&mlx->chvars);
	draw_buttons(mlx, mlx->menuwin);
	draw_btns_names(mlx, mlx->menuwin);
	mlx->chvars.win_ch[1] = 0;
}
