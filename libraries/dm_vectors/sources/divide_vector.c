/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:06:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/24 15:06:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

t_3f	divide_vector(float fact, t_3f *vect1)
{
	t_3f	vect;

	vect.x = vect1->x;
	vect.y = vect1->y;
	vect.z = vect1->z;
	vect.x /= fact;
	vect.y /= fact;
	vect.z /= fact;
	return (vect);
}
