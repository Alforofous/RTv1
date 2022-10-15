/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:45:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:06:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

/*Return a new vector that is perpendicular to given vectors.*/
t_3d	cross_product(t_3d vect1, t_3d vect2)
{
	t_3d	vect;

	vect.x = vect1.y * vect2.z - vect1.z * vect2.y;
	vect.y = vect1.z * vect2.x - vect1.x * vect2.z;
	vect.z = vect1.x * vect2.y - vect1.y * vect2.x;
	return (vect);
}
