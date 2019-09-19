/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:53:54 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 15:25:51 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		main_mouse_press_event(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		vars->mousex = x;
		vars->mousey = y;
	}
	return (0);
}

int		main_mouse_release_event(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		vars->padx += x - vars->mousex;
		vars->pady += y - vars->mousey;
		vars->win_ch[0] = 1;
	}
	return (0);
}