/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:44:40 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 19:07:07 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/header.h"
#include <stdlib.h>
#include <stdio.h>

int		ft_init_default_menu(t_mlx *mlx)
{
	int buttons;
	int		butwid;
	int		buthei;
	if (!(mlx->chvars->btns_cols = (int*)malloc(sizeof(int) * BUTTONS)))
		return (-1);
	ft_bzero((void*)mlx->chvars->btns_cols, BUTTONS * sizeof(int));
	printf("%p\n", mlx->chvars->btns_cols);
	getchar();
	if (!(mlx->chvars->btns_txt = (char**)malloc(sizeof(char*) * (BUTTONS + 1))))
		return (-1);
	mlx->chvars->btns_txt[BUTTONS] = NULL;
	mlx->chvars->btns_txt[0] = ft_strdup("rot X");
	mlx->chvars->btns_txt[1] = ft_strdup("rot Y");
	mlx->chvars->btns_txt[2] = ft_strdup("rot Z");
	mlx->chvars->btns_txt[3] = ft_strdup("reset");
	mlx->chvars->btns_txt[4] = ft_strdup("rotspd +/-");
	mlx->chvars->btns_txt[5] = ft_strdup("zoom +/-");
	mlx->chvars->btns_txt[6] = ft_strdup("red");
	mlx->chvars->btns_txt[7] = ft_strdup("green");
	mlx->chvars->btns_txt[8] = ft_strdup("blue");
	int	x;
	int	y;
	int	i;
	int	j;
	y = 0;
	ft_draw_default_menu(mlx);
	/*
	while (y < MENUWINHEI)
	{
		x = 0;
		while (x < MENUWINWID)
		{
			if ((x % (MENUWINWID / ft_sqrt(buttons))) == 0 || (y % (MENUWINHEI / ft_sqrt(buttons)) == 0))
				*(unsigned*)(mlx->menuwin->data + ((mlx->menuwin->bpx / 8) * x) + (mlx->menuwin->size_line) * y) = 0x00FFFFFF;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->menuwin->win, mlx->menuwin->img, 0, 0);*/


	return (0);
}

void	ft_draw_buttons(t_mlx *mlx, t_win *win)
{
	int	x;
	int	y;
	int	curr_btn;

	y = 0;
	x = 0;
	printf("CABA\n");
	while (x < BUTTONS)
	{
		printf("%X\n", mlx->chvars->btns_cols[x]);
		x++;
	}
	printf("CABB\n");
	while (y < win->hei)
	{
		x = 0;
	printf("CABC\n");
		while (x < win->wid)
		{
			int	tmpx;
			int	tmpy;
			curr_btn = (x * BTN_ROW) / win->wid +
				BTN_COL * ((BTN_COL * y) /(win->hei));
			if ((x % (win->wid / BTN_COL)) == 0 ||
					(y % (win->hei / BTN_ROW) == 0))
			{
				*(unsigned*)(win->data + ((win->bpx / 8) * x) +
						(win->size_line) * y) = WHITE;
			}
//			else if (curr_btn != 7)
			else
				*(unsigned*)(win->data + ((win->bpx / 8) * x) +
						(win->size_line) * y) = mlx->chvars->btns_cols[curr_btn];
//			else
//				ft_draw_gradient_btn(
			x++;
		}
	printf("CABD\n");
		y++;
	}
	printf("CABE|%p|%p|%p\n", mlx->mlx, win->win, win->img);
	mlx_put_image_to_window(mlx->mlx, win->win, win->img, 0, 0);
	printf("CABF\n");
}

void	ft_draw_btns_names(t_mlx *mlx, t_win *win)
{
	int	i;
	int	buthei;
	int	butwid;

	i = 0;
	butwid = win->wid / BTN_ROW;
	buthei = win->hei / BTN_COL;

	while (i < BUTTONS)
	{
		mlx_string_put(mlx->mlx, mlx->menuwin->win,
				((i % BTN_ROW) * butwid + butwid / 2
				 - (butwid / 32) * ft_strlen(mlx->chvars->btns_txt[i])),
				((i / BTN_COL) * buthei + buthei / 3)
				, 0x00FFFFFF, mlx->chvars->btns_txt[i]);
		i++;
	}

}

void	ft_determine_buttons_colors(t_vars *vars)
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
//		mlx->btns_cols[button_pressed] = mlx->chvars->rotspdir > 0 ? BLUE : ORANGE;
//		mlx->btns_cols[button_pressed] = mlx->chvars->zoomdir > 0 ? BLUE : ORANGE;
}

void	ft_draw_default_menu(t_mlx *mlx)
{
	printf("CAA\n");
	ft_determine_buttons_colors(mlx->chvars);
	printf("CAB\n");
	ft_draw_buttons(mlx, mlx->menuwin);
	printf("CAC\n");
	ft_draw_btns_names(mlx, mlx->menuwin);
	printf("CAD\n");
	mlx->chvars->win_ch[1] = 0;
}
