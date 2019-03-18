/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:05:29 by niboute           #+#    #+#             */
/*   Updated: 2019/03/13 17:38:48 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/header.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (0);
	return (1);
}

int		store_str_p2(char *str, t_mlx *mlx, t_point *point, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		point[x].x = x;
		point[x].y = y;
		point[x].z = ft_atoi(str + i);
		if (!mlx->z[0] || point[x].z < mlx->z[0])
			mlx->z[0] = point[x].z;
		if (!mlx->z[1] || point[x].z > mlx->z[1])
			mlx->z[1] = point[x].z;
		i += (str[i] == '-' || str[i] == '+' ? 1 : 0);
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] == ' ')
			i++;
		x++;
	}
	return (1);
}

int		store_str(char *str, t_mlx *mlx, size_t size, int y)
{
	t_fileline	*ptr;
	t_fileline	*tmp;

	if (!(ptr = (t_fileline*)malloc(sizeof(t_fileline))))
		return (-1);
	ptr->next = NULL;
	if (!mlx->lines)
		mlx->lines = ptr;
	else
	{
		tmp = mlx->lines;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ptr;
	}
	if (!(ptr->points = (t_point*)malloc(sizeof(t_point) * (size + 1))))
		return (-1);
	store_str_p2(str, mlx, ptr->points, y);
	return (size);
}

size_t	check_store_str(char *str, t_mlx *mlx, size_t sizeref, int y)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!ft_is_number(str + i))
			return (0);
		size++;
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] == ' ')
			i++;
	}
	if ((size == sizeref && size) || (sizeref == 0 && size))
		store_str(str, mlx, size, y);
	return (size);
}

t_mlx	*ft_read_file(char *name, t_mlx *mlx)
{
	int		fd;
	char	*str;
	size_t	size;
	int		y;

	y = 1;
	mlx->lines = NULL;
	mlx->z[0] = 0;
	mlx->z[1] = 0;
	if ((fd = open(name, O_RDONLY)) < 3)
		return (NULL);
	if ((get_next_line(fd, &str)) <= 0)
		return (NULL);
	if (!(size = check_store_str(str, mlx, 0, 0)))
		return (NULL);
	while ((get_next_line(fd, &str)) > 0)
	{
		if (size != check_store_str(str, mlx, size, y))
			return (NULL);
		ft_memdel((void**)&str);
		y++;
	}
	mlx->gridwid = size;
	mlx->gridhei = y;
	return (ft_setup_mlx(mlx));
}
