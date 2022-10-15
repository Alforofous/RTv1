/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:06:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:32:53 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

t_3d	divide_vector(t_3d vect, double factor)
{
	t_3d	v;

	v.x = vect.x;
	v.y = vect.y;
	v.z = vect.z;
	v.x /= factor;
	v.y /= factor;
	v.z /= factor;
	return (v);
}
