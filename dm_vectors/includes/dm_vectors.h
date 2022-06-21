/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:41:10 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/21 11:32:28 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DM_VECTORS_H
# define DM_VECTORS_H

# include <math.h>

# ifndef PI
#  define PI 3.141592
# endif

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
