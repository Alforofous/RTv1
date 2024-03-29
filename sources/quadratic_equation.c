/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:20:38 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:22:58 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	finite_object(t_3d hit_point, t_object *object)
{
	t_3d	hit_point_to_top;
	double	temp;

	hit_point_to_top = subtract_vectors(hit_point, object->top);
	if (object->axis_length < 0)
		temp = dot_product(hit_point_to_top, object->axis);
	else
		temp = dot_product(hit_point_to_top, scale_vector(object->axis, -1));
	if (temp < 0)
		return (-1);
	else if (temp > fabs(object->axis_length))
		return (-2);
	return (1);
}

static int	assess_t(t_2d *t)
{
	double	temp;

	if (t->x < 0 && t->y < 0)
	{
		t->x = T_MAX;
		t->y = T_MAX;
		return (0);
	}
	if (t->x < 0)
		t->x = t->y;
	if (t->y < 0)
		t->y = T_MAX;
	if (t->x > t->y)
	{
		temp = t->x;
		t->x = t->y;
		t->y = temp;
	}
	return (1);
}

int	quadratic_equation(t_3d quadratic, t_2d one_inter_check, t_2d *t)
{
	double	discr;

	discr = quadratic.y * quadratic.y - 4 * quadratic.x * quadratic.z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		if (one_inter_check.x != one_inter_check.y)
		{
			t->y = -0.5f * quadratic.y / quadratic.x;
			t->x = -0.5f * quadratic.y / quadratic.x;
		}
	}
	else
	{
		t->x = (-quadratic.y - sqrt(discr)) / (2 * quadratic.x);
		t->y = (-quadratic.y + sqrt(discr)) / (2 * quadratic.x);
	}
	return (assess_t(t));
}
