/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/07 14:05:25 by dmalesev         ###   ########.fr       */
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

# define SCREEN_X 2560 / 3
# define SCREEN_Y 1440 / 3
# define IMG_COUNT 14
# define T_MAX 100000000.0f

# ifndef PI
#  define PI 3.141592
# endif

# if __APPLE__
#  include "mac_def.h"
# elif __linux__
#  include "lnx_def.h"
# endif

# include "bitmask_keys.h"

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
	t_2i	size;
	t_2i	start;
	t_2i	end;
}				t_dim;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_dim			dim;
	struct s_img	*next;
	void			(*draw_func)(void *param);
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

typedef struct s_3d
{
	double	x;
	double	y;
	double	z;
}				t_3d;

typedef struct s_3i
{
	int	x;
	int	y;
	int	z;
}				t_3i;

typedef struct s_2f
{
	float	x;
	float	y;
}				t_2f;

typedef struct s_2d
{
	double	x;
	double	y;
}				t_2d;

typedef struct s_2ui
{
	t_uint	x;
	t_uint	y;
}				t_2ui;

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
	t_3f	axis;
	float	axis_length;
	float	lumen;
	float	radius;
	t_uint	color;
	t_2i	shade_coords;
	t_uint	rgb;
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

typedef struct s_utils
{
	void			*mlx;
	void			*win;
	int				dest_color;
	int				visual_rays;
	int				light_render;
	int				tick;
	int				dot_radius;
	int				render;
	int				sel_elem;
	int				add_object_menu;
	t_pxl			pxl[2];
	float			shadow_bias;
	float			scale;
	float			t_max;
	long int		elapsed_time;
	struct timespec	time;
	long int		bitmask_key;
	float			*property[2];
	float			multiplier;
	t_2i			density;
	t_font			*font;
	t_ray			cam;
	t_list			*objects;
	t_object		*closest_object;
	t_object		*sel_object;
	t_3f			rot;
	t_proj			proj;
	t_mat			rmatrix_x;
	t_mat			rmatrix_y;
	t_mat			rmatrix_z;
	t_mouse			mouse;
	t_img			*img;
	t_dim			button;
	t_img			*curr_img;
}				t_utils;

/*Prog functions*/
void	close_prog(void *param, char *exit_msg, int exit_code);

/*Drawing functions*/
void	fill_img(t_utils *utils, t_uint color);
void	put_pixel(t_2i coords, t_uint color, void *param);
void	put_dot(t_2i coords, t_uint color, void *param);
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
void	move_left_button(t_utils *u, int x, int y);
void	hold_left_button(t_utils *u, int x, int y);
void	right_button_down(t_utils *u, int x, int y);
void	move_right_button(t_utils *u, int x, int y);
void	scroll_wheel(t_utils *u, int x, int y);
void	scroll_wheel_up(t_utils *u, int x, int y);
void	scroll_wheel_down(t_utils *u, int x, int y);

/*Keyboard functions*/
int		key_down(int keycode, void *param);
int		key_up(int keycode, void *param);

/*Image functions*/

t_img	*create_images(void *mlx, size_t count);
t_img	*free_images(void * mlx, t_img *img, int i);
void	image_processing(t_utils *utils, t_img *img, t_uint fill_color);
void	draw_image0(void *param);
void	draw_image1(void *param);
void	draw_image2(void *param);
void	draw_image3(void *param);
void	draw_image4(void *param);
void	draw_rgb_slider(void *param);
void	draw_shade_picker(void *param);
void	draw_x(void *param);
void	draw_plus(void *param);
void	draw_increment(void *param);
void	draw_decrement(void *param);
void	draw_lightbulb(void *param);
t_dim	get_button_position(t_2i coords);

/*Display strings functions*/
t_2i	display_str(t_pxl *pxl, t_2i coords, char *str, t_2i color);
t_2i	display_int(t_pxl *pxl, t_2i coords, int nbr, t_2i color);
t_2i	display_float(t_pxl *pxl, t_2i coords, t_2f flt_prec, t_2i color);

/*Init functions*/
void	init(t_utils *utils);
void	init_mlx(t_utils *utils);
void	init_mouse(t_utils *utils);
void	init_camera(t_utils *utils);

/*Help functions*/
int		ft_min(int n1, int n2);
int		coords_in_area(t_dim dim, int x, int y);
int		int_to_bit(int nbr);
void	ft_lowercase(char *c);
int		is_whitespace(char c);
char	*find_last_space(char *str);
int		bound_clipping(t_img *img, t_3f *p);
t_dim	button_coords_in_img(t_dim button, t_dim img);

/*Matrix functions*/
t_proj	init_proj(float fov, t_2i *dim, t_2f *z_depth);
void	init_matrix(t_mat *matrix);
t_mat	init_pmatrix(t_proj *proj);
t_mat	init_rmatrix_x(float angle_x);
t_mat	init_rmatrix_y(float angle_y);
t_mat	init_rmatrix_z(float angle_z);
void	matrix_multip(t_3f *in, t_3f *out, t_mat *matrix);
t_3f	get_points(t_img *img, t_3f *xyz, t_3f *rot, t_proj *proj);

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
int		intersect_sphere(t_3f *ray, t_3f *ray_origin, t_3f *origin, float radius, t_2d *t);
int		intersect_plane(t_3f *ray, t_3f *origin, t_3f *ray_origin, t_3f *normal, double *t);
int		intersect_cone(t_3f *ray_origin, t_3f *ray, t_3f *origin, t_3f *axis, float radius, t_2d *t);
int		intersect_cylinder(t_3f *ray_origin, t_3f *ray, t_3f *origin, t_3f *orient, float radius, t_2d *t);
void	get_camera_directions(t_utils *utils, t_ray *cam);

/*Ray functions*/
void	ray_plotting(t_utils *utils, t_img *img, t_2i coords);
void	put_images_to_window(t_utils *utils);

/*Object functions*/
void		delete_sel_object(t_utils *utils, t_list **objects);
t_object	*select_last(t_list *objects);

/*Create object properties*/
t_object	create_light(t_3f origin, t_uint color, float lumen);
t_object	create_sphere(t_3f origin, t_uint color, float radius);
t_object	create_plane(t_3f origin, t_uint color, t_3f axis);
t_object	create_cone(t_3f origin, t_uint color, t_3f axis, float radius);
t_object	create_cylinder(t_3f origin, t_uint color, t_3f axis, float radius);

/*Drawing sidebard function*/

t_uint	shade_picker(t_img *img, t_2i *coords, t_uint color);
t_uint	rgb_slider(t_img *img, t_2i *coords);
void	add_object_menu(t_utils *utils, int x, int y);
void	change_obj_color(t_img *img, t_object *sel_object, int x, int y);
void	change_obj_property(t_object *sel_object, float nbr);
void	properties(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *object);

/*Scene file parser function*/

t_list	*load_scene(char *path);
t_list	*add_object(t_list *objects, t_object *object);
int		read_object_info(char *line, t_object *object);

#endif
