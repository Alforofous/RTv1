/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_obj_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:07:18 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/16 14:24:29 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	change_obj_color(t_img *img, t_object *sel_object, int x, int y)
{
	sel_object->color = rgb_slider(img, &(t_2i){x, y});
}
