/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:45:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 16:46:16 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

/*Return a new vector that is perpendicular to given vectors.*/
t_3f	cross_product(t_3f *vect1, t_3f *vect2) 
{
	t_3f	vect;

	vect.x = vect1->y * vect2->z - vect1->z * vect2->y;
	vect.y = vect1->z * vect2->x - vect1->x * vect2->z;
	vect.z = vect1->x * vect2->y - vect1->y * vect2->x;
	return (vect);
}
