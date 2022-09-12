/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:48:18 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/09 12:31:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

t_3f	scale_vector(t_3f vect, float factor)
{
	t_3f	v;

	v.x = vect.x;
	v.y = vect.y;
	v.z = vect.z;
	v.x *= factor;
	v.y *= factor;
	v.z *= factor;
	return (v);
}
