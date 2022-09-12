/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:06:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/09 12:30:48 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

t_3f	divide_vector(t_3f vect, float factor)
{
	t_3f	v;

	v.x = vect.x;
	v.y = vect.y;
	v.z = vect.z;
	v.x /= factor;
	v.y /= factor;
	v.z /= factor;
	return (v);
}
