/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_bdfrender.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:31:06 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/19 15:35:19 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DM_BDFRENDER_H
# define DM_BDFRENDER_H

typedef unsigned int	t_uint;

typedef struct s_pxl_func
{
	void	(*f)(int x, int y, t_uint color, void *param);
	void	*param;
}				t_pxl_func;

/*BDFrenderer functions*/


#endif
