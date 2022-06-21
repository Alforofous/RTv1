/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:13:43 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/21 11:30:46 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DM_2D_H
# define DM_2D_H

# include <math.h>

# ifndef PI
#  define PI 3.141592
# endif

typedef struct s_pxl_func
{
	void	(*f)(int x, int y, int color, void *param);
	void	*param;
}				t_pxl_func;

typedef struct s_cols
{
	int	color;
	int	r;
	int	g;
	int	b;
}				t_cols;

typedef struct s_2i
{
	int	x;
	int	y;
}				t_2i;

typedef struct s_line
{
	int	x;
	int	y;
	int	x_dest;
	int	y_dest;
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
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
	int	f;
	int	g;
	int	h;
}				t_quadril;

/*Functions for drawing 2d shapes.*/
void	draw_circle(t_pxl_func *pxl_func, t_2i *coords, int radius, int color);
void	draw_line(t_pxl_func *pxl_func, t_line *line, int color, int d_col);
void	draw_quadrilateral(t_pxl_func *pxl_func, t_quadril *xy, int color);
void	draw_rect(t_pxl_func *pxl_func, t_2i *xy, t_2i *dimen, int color);
void	draw_rectf(t_pxl_func *pxl_func, t_2i *xy, t_2i *dimen, int color);
void	draw_square(t_pxl_func *pxl_func, t_line *xy, int color);
void	draw_trif(t_pxl_func *pxl_func, t_tri *tri, int color);

/*Color functions*/
int		mix_colors(int color, int color2, float percent);
int		combine_rgb(int red, int green, int blue);
void	seperate_rgb(int color, int *red, int *green, int *blue);

/*Helping functions*/
int		abs(int nbr);

#endif
