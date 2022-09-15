/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_magnitude.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:07:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/15 16:16:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

float	vector_magnitude(t_3f vect)
{
	return (sqrtf((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z)));
}
