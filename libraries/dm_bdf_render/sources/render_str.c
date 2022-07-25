/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:03:30 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 11:58:45 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

t_2i	render_str(char *str, t_pxl *pxl, t_2i *crds, t_uint color)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (*crds);
	while (str[i] != '\0')
	{
		render_glyph(str[i], pxl, crds, color);
		i++;
	}
	return (*crds);
}
