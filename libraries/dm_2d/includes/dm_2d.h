/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:13:43 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 15:16:03 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DM_2D_H
# define DM_2D_H

# include <math.h>

# ifndef PI
#  define PI 3.141592
# endif

typedef unsigned int	t_uint;

typedef struct s_pxl_func
{
	void	(*f)(int x, int y, t_uint color, void *param);
	void	*param;
}				t_pxl_func;

typedef struct s_cols
{
	t_uint	color;
	int		r;
	int		g;
	int		b;
}				t_cols;

# ifndef S_2I
#  define S_2I

typedef struct s_2i
{
	int	x;
	int	y;
}				t_2i;
# endif

typedef struct s_line
{
	t_2i	start;
	t_2i	end;
}				t_line;

typedef struct s_tri
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	x3;
	int	y3;
}				t_tri;

typedef struct s_quadril
{
	t_2i	a;
	t_2i	b;
	t_2i	c;
	t_2i	d;
}				t_quadril;

/*Functions for drawing 2d shapes.*/
void	draw_circle(t_pxl_func *pxl, t_2i coords, int radius, t_uint color);
void	draw_circlef(t_pxl_func *pxl, t_2i coords, int radius, t_uint color);
void	draw_line(t_pxl_func *pxl, t_line line, t_uint color, t_uint d_col);
void	draw_quadrilateral(t_pxl_func *pxl, t_quadril xy, t_uint color);
void	draw_rect(t_pxl_func *pxl, t_2i coords, t_2i dimen, t_uint color);
void	draw_rectf(t_pxl_func *pxl, t_2i coords, t_2i dimen, t_uint color);
void	draw_square(t_pxl_func *pxl, t_line line, t_uint color);
void	draw_trif(t_pxl_func *pxl, t_tri tri, t_uint color);

/*Color functions*/
t_uint	transition_colors(t_uint color, t_uint color2, float percent);
t_uint	combine_rgb(int red, int green, int blue);
void	seperate_rgb(t_uint color, int *red, int *green, int *blue);

/*Helping functions*/
int		abs(int nbr);

#endif
