/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:12:25 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 16:11:34 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <unistd.h>
#include "../minilibx_macos/mlx.h"
#include <fcntl.h>
#include <stdlib.h>

void	ft_print_meme(char *name)
{
	char	buff[513];
	int		ret;
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 3)
		return ;
	while ((ret = read(fd, buff, 512)) > 0)
	{
		buff[ret] = '\0';
		ft_putstr(buff);
	}
	close(fd);
}

int		ft_exit(int err)
{
	if (err == 1)
		ft_print_meme("resources/illegal.txt");
	if (err == 2)
		ft_putendl("Invalid map");
	if (err == 3)
		ft_putendl("An error occured\n");
	exit(-1);
}

int		init_default_menu(t_mlx *mlx)
{
	ft_bzero((void*)mlx->chvars.btns_cols, BUTTONS * sizeof(int));
	if (!(mlx->chvars.btns_txt[0] = ft_strdup("rot X")))
		return (0);
	if (!(mlx->chvars.btns_txt[1] = ft_strdup("rot Y")))
		return (0);
	if (!(mlx->chvars.btns_txt[2] = ft_strdup("rot Z")))
		return (0);
	if (!(mlx->chvars.btns_txt[3] = ft_strdup("reset")))
		return (0);
	if (!(mlx->chvars.btns_txt[4] = ft_strdup("rotspd +/-")))
		return (0);
	if (!(mlx->chvars.btns_txt[5] = ft_strdup("zoom +/-")))
		return (0);
	if (!(mlx->chvars.btns_txt[6] = ft_strdup("red")))
		return (0);
	if (!(mlx->chvars.btns_txt[7] = ft_strdup("green")))
		return (0);
	if (!(mlx->chvars.btns_txt[8] = ft_strdup("blue")))
		return (0);
	draw_default_menu(mlx);
	return (1);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	int		fd;

	if (ac != 2)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) < 3)
		return (-1);
	if (!read_file(fd, &mlx))
	{
		close(fd);
		ft_exit(2);
	}
	close(fd);
	if (!setup_mlx(&mlx))
		ft_exit(3);
	mlx_hook(mlx.mainwin->win, 17, 1L << 17, ft_exit, (void*)1);
	if (!(init_default_menu(&mlx)))
		ft_exit(3);
	mlx_loop_hook(mlx.mlx, loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
