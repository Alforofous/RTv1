/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:25:47 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/10 15:33:02 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

#include <math.h>

typedef struct s_3f
{
	float	x;
	float	y;
	float	z;
}				t_3f;

/*Vector operators*/
t_3f	add_vectors(t_3f *vect1, t_3f *vect2);
t_3f	subtract_vectors(t_3f *vect1, t_3f *vect2);
t_3f	scale_vector(float fact, t_3f *vect1);
/*Vector math*/
t_3f	cross_product(t_3f *vect1, t_3f *vect2);
t_3f	normalize_vector(t_3f vect);
float	dot_product(t_3f *vect1, t_3f *vect2);

#endif
