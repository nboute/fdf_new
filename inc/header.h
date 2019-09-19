/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:08:05 by niboute           #+#    #+#             */
/*   Updated: 2019/09/19 16:06:09 by niboute          ###   ########.fr       */
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
# define DARK_GREEN 0X00006633
# define BUTTONS 9
# define BTN_ROW 3
# define BTN_COL 3
# include "../libft/libft.h"

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
	double				rx;
	double				ry;
	double				rz;
	unsigned int		color;
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
	int					wid;
	int					hei;
	int					bpx;
	int					size_line;
	int					endian;
}						t_win;

typedef struct			s_vars
{
    short               mousex;
    short               mousey;
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
	char				*(btns_txt[BUTTONS]);
	int					btns_cols[BUTTONS];
	int					win_ch[2];
	unsigned int		col_start;
	unsigned int		col_end;
	unsigned char		color[6];
	char				slc_col;
	unsigned char		col_ch;
	int					zscale;
	double				z[2];
	int					padx;
	int					padxdir;
	int					pady;
	int					padydir;
}						t_vars;

typedef struct			s_mlx
{
	struct s_fileline	*lines;
	struct s_point		**points;
	void				*mlx;
	struct s_win		*mainwin;
	struct s_win		*menuwin;
	int					gridwid;
	int					gridhei;
	struct s_vars		chvars;
}						t_mlx;

t_mlx					*setup_mlx(t_mlx *mlx);
t_mlx					*read_file(int fd, t_mlx *mlx);
int						bind_events(t_mlx *mlx);
int						ft_exit(int err);
int						loop(t_mlx *mlx);
int						resetvals(t_mlx *mlx);
int						init_default_menu(t_mlx *mlx);
void					draw_buttons(t_mlx *mlx, t_win *win);
void					draw_default_menu(t_mlx *mlx);
void					draw_menu(t_mlx *mlx);
void					reset_all(t_vars *vars);
int						color_grad(unsigned int cola, unsigned int colb,
						int percent);
int						init_menu_win(t_mlx *mlx);
int						menu_mouse_event(int button, int x, int y,
						t_vars *vars);
int						menu_key_event(int keycode, t_vars *vars);
int						main_key_press_event(int keycode, t_vars *vars);
int						main_key_release_event(int keycode, t_vars *vars);
int						menu_mouse_release_event(int button, int x, int y,
						t_vars *vars);
int						main_mouse_release_event(int button, int x, int y,
						t_vars *vars);
int						main_mouse_press_event(int button, int x, int y,
						t_vars *vars);
int						draw_line_select(t_point *a, t_point *b, t_win *win);
int						draw_line(t_point *a, t_point *b, t_win *win);
int						change_n_check_vars(t_vars *vars);
int						rescale_z(t_mlx *mlx);

#endif
