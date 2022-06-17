/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:49:36 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/15 12:00:15 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_3f	add_vectors(t_3f *vect1, t_3f *vect2)
{
	t_3f	vect;

	vect.x = vect1->x + vect2->x;
	vect.y = vect1->y + vect2->y;
	vect.z = vect1->z + vect2->z;
	return (vect);
}

t_3f	subtract_vectors(t_3f *vect1, t_3f *vect2)
{
	t_3f	vect;

	vect.x = vect1->x - vect2->x;
	vect.y = vect1->y - vect2->y;
	vect.z = vect1->z - vect2->z;
	return (vect);
}

t_3f	scale_vector(float fact, t_3f *vect1)
{
	t_3f	vect;
	
	vect.x = vect1->x;
	vect.y = vect1->y;
	vect.z = vect1->z;
	vect.x *= fact;
	vect.y *= fact;
	vect.z *= fact;
	return (vect);
}
