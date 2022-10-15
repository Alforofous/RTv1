/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 12:17:13 by dmalesev         ###   ########.fr       */
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
# include <math.h>
# include <stdio.h>
# include <time.h>

# define SCREEN_X 1000
# define SCREEN_Y 600
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
	double	z_near;
	double	z_far;
	double	fov;
	double	asp_ratio;
	double	fov_rad;
}				t_proj;

typedef struct s_mat
{
	double	m[4][4];
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
	int		button;
	t_2i	move;
	t_2i	pos;
}				t_mouse;

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

typedef struct s_3f
{
	float	x;
	float	y;
	float	z;
}				t_3f;

typedef struct s_2ui
{
	t_uint	x;
	t_uint	y;
}				t_2ui;

typedef struct s_object
{
	t_3d	origin;
	t_3d	axis;
	t_3d	top;
	double	axis_length;
	double	lumen;
	double	radius;
	t_uint	color;
	t_2i	shade_coords;
	t_uint	rgb;
	int		type;
}				t_object;

typedef struct s_dir
{
	t_3d	forward;
	t_3d	back;
	t_3d	up;
	t_3d	down;
	t_3d	right;
	t_3d	left;
}				t_dir;

typedef struct s_ray
{
	t_3d	origin;
	t_3d	dir;
}				t_ray;

typedef struct s_cam
{
	t_3d	origin;
	t_dir	dir;
	t_3d	rot;
}				t_cam;

typedef struct s_utils
{
	void			*mlx;
	void			*win;
	int				dest_color;
	int				visual_rays;
	int				rend_lights;
	int				tick;
	int				dot_radius;
	int				render;
	int				sel_elem;
	int				add_object_menu;
	t_pxl			pxl[2];
	double			shadow_bias;
	double			scale;
	double			t_max;
	long int		bitmask_key;
	double			*property[2];
	double			multiplier;
	double			hold_time;
	t_cam			cam;
	t_2i			density;
	t_font			*font;
	t_list			*scene;
	t_object		*closest_object;
	t_object		*sel_object;
	t_3d			rot;
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
void		close_prog(void *param, char *exit_msg, int exit_code);

/*Drawing functions*/
void		fill_img(t_utils *utils, t_uint color);
void		put_pixel(t_2i coords, t_uint color, void *param);
void		put_dot(t_2i coords, t_uint color, void *param);
void		render_screen(t_utils *utils);
void		draw_image0(void *param);
void		draw_image1(void *param);
void		draw_image2(void *param);
void		draw_image3(void *param);
void		draw_image4(void *param);
void		draw_rgb_slider(void *param);
void		draw_shade_picker(void *param);
void		draw_x(void *param);
void		draw_plus(void *param);
void		draw_increment(void *param);
void		draw_decrement(void *param);
void		draw_lightbulb(void *param);

/*Hook functions*/
int			prog_clock(void *param);
int			on_destroy(void *param);

/*Mouse functions*/
int			mouse_move(int x, int y, void *param);
int			mouse_up(int button, int x, int y, void *param);
int			mouse_down(int button, int x, int y, void *param);
void		left_button_down(t_utils *utils, int x, int y);
void		move_right_button(t_utils *utils, int x, int y);
void		hold_right_button(t_utils *utils, int x, int y);
void		scroll_wheel(t_utils *utils, int x, int y);
void		scroll_wheel_up(t_utils *utils, int x, int y);
void		scroll_wheel_down(t_utils *utils, int x, int y);
void		mouse_hold_elem(t_utils *utils, int elem);

/*Keyboard functions*/
int			key_down(int keycode, void *param);
int			key_up(int keycode, void *param);
void		press_once(t_utils *utils, int key);
void		keyboard_hold_key(long int bmk, t_utils *utils, t_dir *dir);

/*Image functions*/
t_img		*create_images(void *mlx, size_t count);
t_img		*free_images(void *mlx, t_img *img, int i);
void		image_processing(t_utils *u, t_img *img, t_uint fill_col, int mode);

/*Display strings functions*/
t_2i		display_str(t_pxl *pxl, t_2i coords, char *str, t_2i color);
t_2i		display_int(t_pxl *pxl, t_2i coords, int nbr, t_2i color);
t_2i		display_double(t_pxl *pxl, t_2i coords, t_2d flt_prec, t_2i color);

/*Init functions*/
void		init(t_utils *utils);
void		init_mlx(t_utils *utils);
void		init_mouse(t_utils *utils);
void		init_camera(t_cam *cam);

/*Help functions*/
int			ft_min(int n1, int n2);
int			coords_in_area(t_dim dim, int x, int y);
int			int_to_bit(int nbr);
void		ft_lowercase(char *c);
int			is_whitespace(char c);
char		*find_last_space(char *str);
int			bound_clipping(t_img *img, t_3d *p);
t_dim		button_coords_in_img(t_dim button, t_dim img);
double		time_since_success(double ammount, int id);

/*Matrix functions*/
t_proj		init_proj(double fov, t_2i *dim, t_2d *z_depth);
void		init_matrix(t_mat *matrix);
t_mat		init_pmatrix(t_proj *proj);
t_mat		init_rmatrix_x(double angle_x);
t_mat		init_rmatrix_y(double angle_y);
t_mat		init_rmatrix_z(double angle_z);
void		matrix_multip(t_3d *in, t_3d *out, t_mat *matrix);
t_3d		get_points(t_img *img, t_3d *xyz, t_3d *rot, t_proj *proj);
t_3d		rotate_point(t_3d point, t_3d rot);

/*Objects and vertices*/
t_3d		calculate_normal(t_object *object, t_3d hit_point, t_2d t);
t_uint		light_up(t_list *scene, t_uint color, t_ray to_light, t_3d normal);

/*Cam functions*/
void		get_camera_directions(t_utils *utils, t_cam *cam);
t_ray		get_ray(t_2i coords, t_img *img, t_cam *cam, t_proj *proj);

/*Intersect functions*/
int			intersect_sphere(t_ray ray, t_object *sphere, t_2d *t);
int			intersect_plane(t_ray ray, t_object *plane, t_2d *t);
int			intersect_cylinder(t_ray ray, t_object *object, t_2d *t);
int			intersect_cone(t_ray ray, t_object *object, t_2d *t);
int			quadratic_equation(t_3d quadratic, t_2d one_inter_check, t_2d *t);
int			finite_object(t_3d hit_point, t_object *object);
t_2d		closest_t(t_list *scene, t_object **clo_obj, t_ray ray, int mode);

/*Ray functions*/
t_uint		ray_trace(t_utils *u, t_object **clo_obj, t_list *scene, t_ray ray);
void		put_images_to_window(t_utils *utils);

/*Object functions*/
void		delete_sel_object(t_utils *utils, t_list **scene);
void		del_object(void *content, size_t content_size);
t_object	*select_last(t_list *scene);

/*Create object properties*/
t_object	create_light(t_3d origin, t_uint color, double lumen);
t_object	create_sphere(t_3d origin, t_uint color, double radius);
t_object	create_plane(t_3d origin, t_uint color, t_3d axis);
t_object	create_cone(t_3d origin, t_uint color, t_3d axis, double radius);
t_object	create_cylinder(t_3d ori, t_uint color, t_3d axis, double radius);

/*Drawing sidebard function*/
t_uint		shade_picker(t_img *img, t_2i *coords, t_uint color);
t_uint		rgb_slider(t_img *img, t_2i *coords);
void		add_object_menu(t_utils *utils, int x, int y);
void		change_obj_color(t_img *img, t_object *sel_object, int x, int y);
void		change_obj_property(t_object *sel_object, double nbr);
void		properties(t_utils *utils, t_pxl *pxl, t_2i coords, t_object *obj);

/*Scene file parser function*/
t_list		*load_scene(char *path);
t_cam		load_camera(char *path, t_cam camera);
int			read_object_info(char *line, t_object *object);
int			read_camera_info(char *line, t_cam *cam);
int			add_object(t_list **scene, t_object *object);
int			transformations(char *line, t_object *object);

#endif
