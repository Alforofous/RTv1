/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_magnitude.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:07:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:07:44 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

double	vector_magnitude(t_3d vect)
{
	return (sqrt((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z)));
}
