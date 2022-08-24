/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/24 11:14:22 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "dm_2d.h"
# include "dm_bdf_render.h"
# include "dm_vectors.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# define SCREEN_X 2560 / 2
# define SCREEN_Y 1440 / 2
# ifndef PI
#  define PI 3.141592
# endif

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

typedef struct s_triobj
{
	t_4f	*vertices;
	t_faces	*faces;
	t_3f	*normals;
	int		vert_count;
	int		face_count;
	int		normal_count;
}				t_triobj;

typedef struct s_object
{
	t_3f	origin;
	t_3f	normal;
	t_uint	color;
	float	radius;
	int		type;
}				t_object;

typedef struct	s_dir
{
	t_3f	forward;
	t_3f	back;
	t_3f	up;
	t_3f	down;
	t_3f	right;
	t_3f	left;
}				t_dir;

typedef struct	s_ray
{
	t_3f	origin;
	t_dir	dir;
}				t_ray;

typedef struct	s_light
{
	t_3f	origin;
	t_3f	dir;
	t_3f	color;
	float	lumen;
}				t_light;

typedef struct s_utils
{
	void			*mlx;
	void			*win;
	int				dest_color;
	int				visual_rays;
	int				tick;
	int				dot_radius;
	int				render;
	int				slider_button;
	int				add_object_popup;
	long int		elapsed_time;
	struct timespec	time;
	t_2i			density;
	t_font			*font;
	t_font			*font2;
	t_light			light[100];
	t_ray			cam;
	t_list			*objects;
	t_object		*closest_object;
	t_object		*sel_object;
	t_3f			rot;
	t_proj			proj;
	t_mat			pmatrix;
	t_mat			rmatrix_x;
	t_mat			rmatrix_y;
	t_mat			rmatrix_z;
	t_mouse			mouse;
	t_img			img;
	t_img			img2;
	t_img			img3;
	t_img			img4;
	t_img			img5;
	t_img			img6;
	t_img			img7;
	t_img			*curr_img;
}				t_utils;

typedef struct s_2f
{
	float	x;
	float	y;
}				t_2f;

/*Prog functions*/
void	close_prog(t_utils *utils, char *exit_msg, int exit_code);

/*Drawing functions*/
void	fill_img(t_utils *utils, t_uint color);
void	put_pixel(int x, int y, t_uint color, void *param);
void	put_dot(int x, int y, t_uint color, void *param);
void	render_screen(t_utils *utils);

/*Hook functions*/
int		prog_clock(void *param);
int		on_destroy(void *param);

/*Mouse functions*/
int		mouse_move(int x, int y, void *param);
int		mouse_up(int button, int x, int y, void *param);
int		mouse_down(int button, int x, int y, void *param);
void	left_button_up(t_utils *u, int x, int y);
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
void	image_processing(t_utils *utils, t_img *img, t_uint fill_color);
void	draw_image1(t_utils *utils);
void	draw_image2(t_utils *utils);
void	draw_image3(t_utils *utils);
void	draw_image4(t_utils *utils);
void	draw_image5(t_utils *utils);
void	draw_image6(t_utils *utils);
void	draw_image7(t_utils *utils);

/*Display strings functions*/
t_2i	display_str(t_utils *utils, t_2i coords, t_font *font, char *str);
t_2i	display_int(t_utils *utils, t_2i coords, t_font *font, int nbr);
t_2i	display_float(t_utils *utils, t_2i coords, t_font *font, float nbr);

/*Init functions*/
void	init(t_utils *utils);
void	init_hooks(t_utils *utils);
void	init_values(t_utils *utils);
void	init_mouse(t_utils *utils);
void	init_camera(t_utils *utils);

/*Help functions*/
int		ft_min(int n1, int n2);
int		coords_in_img(t_img *img, int x, int y);
int		int_to_bit(int nbr);
void	ft_lowercase(char *c);
int		is_whitespace(char c);
char	*find_last_space(char *str);
int		bound_clipping(t_img *img, t_3f *p);
void	print_node(t_list *node);

/*Matrix functions*/
t_proj	init_proj(float fov, t_2i *dim, t_2f *z_depth);
void	init_matrix(t_mat *matrix);
t_mat	init_pmatrix(t_proj *proj);
t_mat	init_rmatrix_x(float angle_x);
t_mat	init_rmatrix_y(float angle_y);
t_mat	init_rmatrix_z(float angle_z);
void	matrix_multip(t_3f *in, t_3f *out, t_mat *matrix);
void	scale_into_view(t_utils *utils, float *x, float *y);
void	scale_depth(t_utils *utils, float *z);
t_3f	get_points(t_utils *utils, t_3f *xyz, t_3f *rot, t_proj *proj);

/*Objects and vertices*/
void	load_obj(char *path, t_triobj *obj);
int		malloc_obj_params(t_triobj *obj);
int		obj_param_err_check(t_triobj *obj, int ret);
void	plot_object(t_utils *utils, t_triobj *obj, t_3f *offset, t_uint color);
void	plot_object_vert(t_utils *utils, t_triobj *obj, t_3f *offset, t_uint color);
int		get_obj_params(int fd, t_triobj *obj);
void	print_obj_params(t_triobj *obj);

/*Cam functions*/
t_3f	get_ray(t_2f screen_coords, t_ray *cam, t_proj *proj);
int		intersect_sphere(t_3f *ray, t_3f *origin, float radius, t_2f *t);
int		intersect_plane(t_3f *ray, t_3f *origin, t_3f *ray_origin, t_3f *normal, float *t);
void	get_camera_directions(t_utils *utils, t_ray *cam);

/*Ray functions*/
void	ray_plotting(t_utils *utils, t_img *img, t_2i coords);
void	put_screen(t_utils *utils);

/*Object functions*/
void	delete_sel_object(t_utils *utils, t_list **objects);

#endif
