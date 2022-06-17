/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 11:57:07 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "dm_2d.h"
# include "vectors.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# define SCREEN_X 1200 / 2
# define SCREEN_Y 1000 / 2
# define PI 3.141592

# if __APPLE__
#  include "mac_def.h"
# elif __linux__
#  include "lnx_def.h"
# endif

typedef struct s_proj
{
	float	z_near;
	float	z_far;
	float	fov;
	float	asp_ratio;
	float	fov_rad;
}				t_proj;

typedef struct s_mat
{
	float	m[4][4];
}				t_mat;

typedef struct s_dim
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	width;
	int	height;
}				t_dim;

typedef struct s_utils	t_utils;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_dim			dim;
	struct s_img	*next;
	void			(*draw_func)(t_utils *utils);
}				t_img;

typedef struct s_mouse
{
	int			button;
	int			move_x;
	int			move_y;
	int			zoom_x;
	int			zoom_y;
	int			x;
	int			y;
	int			zoom;
}				t_mouse;

typedef struct s_4f
{
	float	a;
	float	b;
	float	c;
	float	d;
}				t_4f;

typedef struct s_6i
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
	int	f;
}				t_6i;

typedef struct s_4i
{
	int	a;
	int	b;
	int	c;
	int	d;
}				t_4i;

typedef struct s_faces
{
	int	a[3];
	int	b[3];
	int	c[3];
}				t_faces;

typedef struct s_3i
{
	int	x;
	int	y;
	int	z;
}				t_3i;

typedef struct s_obj
{
	t_4f	*vertices;
	t_faces	*faces;
	t_3f	*normals;
	int		vert_count;
	int		face_count;
	int		normal_count;
}				t_obj;

typedef struct	s_objs
{
	t_obj	cube;
	t_obj	sphere;
	t_obj	teapot;
	t_obj	monkey;
	t_obj	diamond;
	t_obj	abstract;
}				t_objs;

typedef struct	s_dir
{
	t_3f	forward;
	t_3f	back;
	t_3f	up;
	t_3f	down;
	t_3f	right;
	t_3f	left;
}				t_dir;

typedef struct	s_cam
{
	t_3f	origin;
	t_dir	dir;
}				t_cam;

typedef struct s_utils
{
	void	*mlx;
	void	*win;
	int		dest_color;
	int		reference;
	int		visual_rays;
	int		tick;
	int		slider_button;
	t_cam	cam;
	t_objs	objects;
	t_3f	rot;
	t_proj	proj;
	t_mat	pmatrix;
	t_mat	rmatrix_x;
	t_mat	rmatrix_y;
	t_mat	rmatrix_z;
	t_mouse	mouse;
	t_img	img;
	t_img	img2;
	t_img	*curr_img;
}				t_utils;

typedef struct s_2f
{
	float	x;
	float	y;
}				t_2f;

/*Prog functions*/
void	close_prog(t_utils *utils, char *exit_msg, int exit_code);
/*Drawing functions*/
void	draw_n_line(t_utils *utils, t_line *line, int len, int color);
void	ft_clear_img(t_utils *utils);
void	ft_pixel_put(int x, int y, int color, void *param);
void	render_screen(t_utils *utils);
/*Hook functions*/
int		prog_clock(void *param);
int		on_destroy(void *param);
/*Mouse functions*/
int		mouse_move(int x, int y, void *param);
int		mouse_up(int button, int x, int y, void *param);
int		mouse_down(int button, int x, int y, void *param);
void	left_button_up(t_utils *u);
void	left_button_down(t_utils *u, int x, int y);
void	hold_left_button(t_utils *u, int x, int y);
void	right_button_down(t_utils *u, int x, int y);
void	hold_right_button(t_utils *u, int x, int y);
void	scroll_wheel(t_utils *u, int x, int y);
void	scroll_wheel_up(t_utils *u, int x, int y);
void	scroll_wheel_down(t_utils *u, int x, int y);
/*Keyboard functions*/
int		key_down(int keycode, void *param);
/*Image functions*/
void	draw_image1(t_utils *utils);
void	draw_image2(t_utils *utils);
/*Init functions*/
void	init(t_utils *utils);
void	init_hooks(t_utils *utils);
void	init_values(t_utils *utils);
void	init_mouse(t_utils *utils);
/*Help functions*/
int		coords_in_img(t_img *img, int x, int y);
int		int_to_bit(int nbr);
void	ft_lowercase(char *c);
int		is_whitespace(char c);
char	*find_last_space(char *str);
/*Matrix functions*/
void	init_proj(t_utils *utils);
void	init_matrix(t_mat *matrix);
void	init_pmatrix(t_utils *u);
void	init_rmatrix_x(t_utils *u);
void	init_rmatrix_y(t_utils *u);
void	init_rmatrix_z(t_utils *u);
void	matrix_multip(t_3f *in, t_3f *out, t_mat *matrix);
void	scale_into_view(t_utils *utils, float *x, float *y);
void	scale_depth(t_utils *utils, float *z);
t_3f	get_points(t_utils *utils, float x, float y, float z);
/*Objects and vertices*/
void	load_obj(char *path, t_obj *obj);
int		malloc_obj_params(t_obj *obj);
int		obj_param_err_check(t_obj *obj, int ret);
void	plot_object(t_utils *utils, t_obj *obj, t_3f *offset, int color);
void	plot_object_vert(t_utils *utils, t_obj *obj, t_3f *offset, int color);
int		get_obj_params(int fd, t_obj *obj);
void	print_obj_params(t_obj *obj);
/*cam functions*/
t_3f	get_ray(t_utils *utils, t_2f screen_coords, t_3f forwards);
int		intersect_sphere(t_3f *ray, t_3f *orig, t_3f *center, float radius);

#endif
