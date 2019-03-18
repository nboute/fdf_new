/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:08:05 by niboute           #+#    #+#             */
/*   Updated: 2019/03/18 18:06:48 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define MAINWINWID 1280
# define MAINWINHEI 960
# define MENUWINWID 400
# define MENUWINHEI 400
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define LIGHT_GREEN 0x007FFF00
# define RED 0x00FF0000
# define BLUE 0x003333FF
# define ORANGE 0x00FF7F00
# define BUTTONS 9
# define BTN_ROW 3
# define BTN_COL 3
#include "../libft/libft.h"

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
	double				rx;
	double				ry;
	double				rz;
}						t_point;

typedef struct			s_fileline
{
	struct s_point		*points;
	struct s_fileline	*next;
}						t_fileline;

typedef struct			s_win
{
	void				*win;
	void				*img;
	char				*data;
	size_t				wid;
	size_t				hei;
	int					bpx;
	int					size_line;
	int					endian;
}						t_win;

typedef struct			s_vars
{
	float				rotspdir;
	double				zoomdir;
	double				defaultzoom;
	double				zoom;
	char				rotx;
	char				roty;
	char				rotz;
	float				rotxval;
	float				rotyval;
	float				rotzval;
	float				rotspd;
	char				**btns_txt;
	int					*btns_cols;
	int					win_ch[2];
	unsigned int		col_start;
	unsigned int		col_end;
}						t_vars;

typedef struct			s_mlx
{
	struct s_fileline	*lines;
	struct s_point		**points;
	void				*mlx;
	struct s_win		*mainwin;
	struct s_win		*menuwin;
	size_t				gridwid;
	size_t				gridhei;
	int					zscale;
	double				z[2];
	struct s_vars		*chvars;
}						t_mlx;

t_mlx	*ft_setup_mlx(t_mlx *mlx);
t_mlx	*ft_read_file(char *name, t_mlx *mlx);
int		ft_bind_events(t_mlx *mlx);
int		ft_exit();
int		ft_loop(t_mlx *mlx);
void	ft_draw(t_mlx *mlx);
int		ft_resetvals(t_mlx *mlx);
int		ft_init_default_menu(t_mlx *mlx);
void	ft_draw_buttons(t_mlx *mlx, t_win *win);
void	ft_draw_default_menu(t_mlx *mlx);
void	ft_draw_menu(t_mlx *mlx);
void	ft_reset_all(t_vars *vars);

#endif
