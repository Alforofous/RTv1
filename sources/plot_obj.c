/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:24:31 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 11:02:40 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plot_object_vert(t_utils *utils, t_obj *obj, t_3f *offset, int color)
{
	t_3f	point;
	int		i;

	i = 0;
	while (i < obj->vert_count)
	{
		point = get_points(utils, obj->vertices[i].a + offset->x,
				obj->vertices[i].b + offset->y,
				obj->vertices[i].c + offset->z);
		if (point.z > 1)
			ft_pixel_put((int)point.x, (int)point.y, color,
				(void *)utils->curr_img);
		i++;
	}
}

static int	bound_clipping(t_img *img, t_3f *p)
{
	int	x[3];
	int	y[3];

	x[0] = (int)p[0].x + img->dim.x0;
	y[0] = (int)p[0].y + img->dim.y0;
	x[1] = (int)p[1].x + img->dim.x0;
	y[1] = (int)p[1].y + img->dim.y0;
	x[2] = (int)p[2].x + img->dim.x0;
	y[2] = (int)p[2].y + img->dim.y0;
	if (coords_in_img(img, x[0], y[0]) && coords_in_img(img, x[1], y[1])
		&& coords_in_img(img, x[2], y[2]))
		return (1);
	return (0);
}

static void	depth_buffer(t_3f *tri)
{
	tri++;
}

void	plot_object(t_utils *utils, t_obj *obj, t_3f *os, int color)
{
	t_3f	p[3];
	t_3f	light;
	float	l;
	float	dp;
	int		i;

	i = 0;
	depth_buffer(&(p[0]));
	while (i < obj->face_count)
	{
		p[0] = get_points(utils, obj->vertices[obj->faces[i].a[0] - 1].a + os->x,
				obj->vertices[obj->faces[i].a[0] - 1].b + os->y,
				obj->vertices[obj->faces[i].a[0] - 1].c + os->z);
		p[1] = get_points(utils, obj->vertices[obj->faces[i].b[0] - 1].a + os->x,
				obj->vertices[obj->faces[i].b[0] - 1].b + os->y,
				obj->vertices[obj->faces[i].b[0] - 1].c + os->z);
		p[2] = get_points(utils, obj->vertices[obj->faces[i].c[0] - 1].a + os->x,
				obj->vertices[obj->faces[i].c[0] - 1].b + os->y,
				obj->vertices[obj->faces[i].c[0] - 1].c + os->z);
		//if (obj == &utils->cube)
		//{
			light.x = 0.5f;
			light.y = 0.0f;
			light.z = 0.0f;
			l = sqrtf(light.x * light.x + light.y * light.y + light.z * light.z);
			light.x /= l;
			light.y /= l;
			light.z /= l;
			dp = (float)obj->normals[obj->faces[i].a[1] - 1].x * light.x
				+ (float)obj->normals[obj->faces[i].a[1] - 1].y * light.y
				+ (float)obj->normals[obj->faces[i].a[1] - 1].z * light.z;
		//	printf("NORMAL VALUE: %f\n", obj->normals[obj->faces[i].a[1] - 1].x);
		//	printf("DOT PRODUCT: %f\n", dp);
		//}
		if (p[0].z > 1 && p[1].z > 1 && p[2].z > 1
			&& bound_clipping(utils->curr_img, &(p[0])))
		{
			if (dp >= 0 && dp <= 1)
				draw_trif(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_tri){(int)p[0].x, (int)p[0].y, (int)p[1].x,
					(int)p[1].y, (int)p[2].x, (int)p[2].y}, mix_colors(color, 0xFFFFFF, dp));
			else if (dp <= -0.1 && dp >= -1)
				draw_trif(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_tri){(int)p[0].x, (int)p[0].y, (int)p[1].x,
					(int)p[1].y, (int)p[2].x, (int)p[2].y}, mix_colors(color, 0x000000, dp * -1));
			else
				draw_trif(&(t_pxl_func){&ft_pixel_put, (void *)utils->curr_img}, &(t_tri){(int)p[0].x, (int)p[0].y, (int)p[1].x,
					(int)p[1].y, (int)p[2].x, (int)p[2].y}, color);
		}
		i++;
	}
}
