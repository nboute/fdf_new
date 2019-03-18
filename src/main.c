/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:12:25 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 14:22:44 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

#include <unistd.h>
#include "../minilibx_macos/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int		ft_exit()
{
	printf("Wait.... thats illegal\n");
	exit(-1);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	if (ac != 2)
		return (0);
	printf("Aok\n");
	if (!ft_read_file(av[1], &mlx))
	{
		return (0);
	}
	printf("Bok\n");
	ft_bind_events(&mlx);
	int	i;
	i = 0;
	int j;
	while (i < mlx.gridhei)
	{
		j = 0;
		while (j < mlx.gridwid)
		{
			printf("%f ", mlx.points[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
//	ft_resetvals(&mlx);
//	ft_draw(&mlx);
	printf("OK\n");
	ft_init_default_menu(&mlx);
	mlx_loop_hook(mlx.mlx, ft_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
