/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_params_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:40:25 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/18 12:38:15 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

static int	fontboundingbox(char *line, t_font *font)
{
	char	*str;

	str = "FONTBOUNDINGBOX";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
			font->bound_box[0] = (t_uint)ft_atoi(line++);
		line = ft_strchr(line, ' ');
		if (line)
			font->bound_box[1] = (t_uint)ft_atoi(line++);
		line = ft_strchr(line, ' ');
		if (line)
			font->offset[0] = ft_atoi(line++);
		line = ft_strchr(line, ' ');
		if (line)
			font->offset[1] = ft_atoi(line++);
		return (1);
	}
	return (0);
}

int	params_branch(char *line, t_font *font)
{
	if (fontboundingbox(line, font))
		return (1);
	return (0);
}
