/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:29:28 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/21 11:31:38 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/*Returns vector with magnitude of |1|*/
t_3f	normalize_vector(t_3f vect)
{
	float	w;

	w = (float)sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	vect.x /= w;
	vect.y /= w;
	vect.z /= w;
	return (vect);
}

/*If vectors are similar value is positive. If vectors are perpendicular to
each other, value is 0. Otherwise value is negative.*/
float	dot_product(t_3f *vect1, t_3f *vect2)
{
	return (vect1->x * vect2->x + vect1->y * vect2->y + vect1->z * vect2->z);
}

/*Return a new vector that is perpendicular to given vectors.*/
t_3f	cross_product(t_3f *vect1, t_3f *vect2)
{
	t_3f	vect;

	vect.x = vect1->y * vect2->z - vect1->z * vect2->y;
	vect.y = vect1->z * vect2->x - vect1->x * vect2->z;
	vect.z = vect1->x * vect2->y - vect1->y * vect2->x;
	return (vect);
}
