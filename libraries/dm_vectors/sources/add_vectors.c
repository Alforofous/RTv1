/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:44:18 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:06:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

t_3d	add_vectors(t_3d vect1, t_3d vect2)
{
	t_3d	vect;

	vect.x = vect1.x + vect2.x;
	vect.y = vect1.y + vect2.y;
	vect.z = vect1.z + vect2.z;
	return (vect);
}
