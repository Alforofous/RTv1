/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:46:23 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/05 11:40:13 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_vectors.h"

/*If vectors are similar value is positive. If vectors are perpendicular to
each other, value is 0. Otherwise value is negative.*/
float	dot_product(t_3f vect1, t_3f vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z);
}
