/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:05:29 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 06:48:45 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/header.h"
#include <fcntl.h>
#include <stdlib.h>

int				ft_is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (0);
	return (1);
}

int				store_str_p2(char *str, t_mlx *mlx, t_point *point, int y)
{
	int			i;
	int			x;
	static char	a = 0;

	i = 0;
	x = 0;
	while (str[i])
	{
		point[x].x = x;
		point[x].y = y;
		point[x].z = ft_atoi(str + i);
		point[x].color = WHITE;
		if (!a || point[x].z < mlx->chvars->z[0])
			mlx->chvars->z[0] = point[x].z;
		if (!a || point[x].z > mlx->chvars->z[1])
			mlx->chvars->z[1] = point[x].z;
		a = 1;
		i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] == ' ')
			i++;
		x++;
	}
	return (1);
}

int				store_str(char *str, t_mlx *mlx, size_t size, int y)
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

size_t			check_store_str(char *str, t_mlx *mlx, size_t sizeref, int y)
{
	size_t		size;
	int			i;

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
	if (str)
		ft_memdel((void**)&str);
	return (size);
}

t_mlx			*ft_read_file(int fd, t_mlx *mlx)
{
	char		*str;
	size_t		size;
	int			y;

	y = 1;
	mlx->lines = NULL;
	mlx->chvars->z[1] = 0;
	if ((get_next_line(fd, &str)) <= 0)
	{
		return (NULL);
	}
	if (!(size = check_store_str(str, mlx, 0, 0)))
		return (NULL);
	while ((get_next_line(fd, &str)) > 0)
	{
		if (size != check_store_str(str, mlx, size, y))
			return (NULL);
		y++;
	}
	mlx->gridwid = size;
	mlx->gridhei = y;
	return (mlx);
}
