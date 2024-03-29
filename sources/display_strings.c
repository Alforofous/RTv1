/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:56:48 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:19:39 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_2i	display_str(t_pxl *pxl, t_2i coords, char *str, t_2i color)
{
	render_str(str, pxl, &(t_2i){coords.x + 1, coords.y + 1}, (t_uint)color.x);
	coords = render_str(str, pxl, &(t_2i){coords.x, coords.y}, (t_uint)color.y);
	return (coords);
}

t_2i	display_double(t_pxl *pxl, t_2i coords, t_2d flt_prec, t_2i color)
{
	char	*str;

	str = ft_ftoa(flt_prec.x, (size_t)flt_prec.y);
	if (str == NULL)
		close_prog(NULL, "Failed to malloc for str in display_double...", -1);
	coords = display_str(pxl, coords, str, color);
	free(str);
	return (coords);
}

t_2i	display_int(t_pxl *pxl, t_2i coords, int nbr, t_2i color)
{
	char	*str;

	str = ft_itoa(nbr);
	if (str == NULL)
		close_prog(NULL, "Failed to malloc for str in display_int...", -1);
	coords = display_str(pxl, coords, str, color);
	free(str);
	return (coords);
}
