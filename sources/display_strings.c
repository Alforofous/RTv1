/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:56:48 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 16:26:59 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_2i	display_str(t_utils *utils, t_2i coords, t_font *font, char *str)
{
	t_pxl	pxl;

	pxl.font = font;
	pxl.f = &ft_pixel_put;
	pxl.param = utils->curr_img;
	render_str(str, &pxl, &(t_2i){coords.x + 2, coords.y + 2}, 0x000000);
	coords = render_str(str, &pxl, &(t_2i){coords.x, coords.y}, 0xFFFFFF);
	return (coords);
}

t_2i	display_float(t_utils *utils, t_2i coords, t_font *font, float nbr)
{
	char	*str;

	str = ft_ftoa(nbr, 3);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for str in display_float...", -1);
	coords = display_str(utils, coords, font, str);
	free(str);
	return (coords);
}

t_2i	display_int(t_utils *utils, t_2i coords, t_font *font, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	if (str == NULL)
		close_prog(utils, "Failed to malloc for str in display_int...", -1);
	coords = display_str(utils, coords, font, str);
	free(str);
	return (coords);
}
