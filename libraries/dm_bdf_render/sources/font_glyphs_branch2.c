/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_glyphs_branch2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:46:34 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 13:53:31 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

static void	offset(char *line, t_font *font)
{
	if (line)
	{
		font->glyphs[font->glyph_i].offset[0] = ft_atoi(line);
		line = ft_strchr(++line, ' ');
	}
	if (line)
		font->glyphs[font->glyph_i].offset[1] = ft_atoi(line);
}

static int	boundingbox(char *line, t_font *font)
{
	char	*str;

	str = "BBX";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
		{
			font->glyphs[font->glyph_i].bound_box[0] = (t_uint)ft_atoi(line);
			line = ft_strchr(++line, ' ');
		}
		if (line)
		{
			font->glyphs[font->glyph_i].bound_box[1] = (t_uint)ft_atoi(line);
			line = ft_strchr(++line, ' ');
		}
		offset(line, font);
		return (1);
	}
	return (0);
}

int	glyphs_branch2(char *line, t_font *font)
{
	if (boundingbox(line, font))
		return (1);
	return (0);
}
