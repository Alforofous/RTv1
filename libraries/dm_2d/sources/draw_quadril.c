/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_quadril.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:22:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/04 15:17:24 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_2d.h"

void	draw_quadrilateral(t_pxl_func *pxl_func, t_quadril quad, t_uint color)
{
	draw_line(pxl_func, (t_line){quad.a, quad.b}, color, color);
	draw_line(pxl_func, (t_line){quad.b, quad.c}, color, color);
	draw_line(pxl_func, (t_line){quad.c, quad.d}, color, color);
	draw_line(pxl_func, (t_line){quad.d, quad.a}, color, color);
}
