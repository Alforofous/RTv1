/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:46:48 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/17 16:47:02 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

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
