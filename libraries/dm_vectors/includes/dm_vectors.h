/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:41:10 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:21:35 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DM_VECTORS_H
# define DM_VECTORS_H

# include <math.h>

# ifndef PI
#  define PI 3.141592
# endif

typedef struct s_3d
{
	double	x;
	double	y;
	double	z;
}				t_3d;

/*Vector operators*/
t_3d	add_vectors(t_3d vect1, t_3d vect2);
t_3d	subtract_vectors(t_3d vect1, t_3d vect2);
t_3d	scale_vector(t_3d vect, double factor);
t_3d	divide_vector(t_3d vect, double factor);
/*Vector math*/
t_3d	cross_product(t_3d vect1, t_3d vect2);
t_3d	normalize_vector(t_3d vect);
double	dot_product(t_3d vect1, t_3d vect2);
double	vector_magnitude(t_3d vect);

#endif
