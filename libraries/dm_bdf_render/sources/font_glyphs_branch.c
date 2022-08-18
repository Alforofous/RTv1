/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_glyphs_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 07:59:36 by dmalesev          #+#    #+#             */
/*   Updated: 2022/08/18 12:38:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

static int	startchar(char *line, t_font *font)
{
	char	*str;

	str = "STARTCHAR";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
		{
			while (*line == ' ')
				line++;
			while (ft_isdigit(*line) == 0 && *line != '\0')
				line++;
			if (*line)
				font->glyphs[font->glyph_i].unicode = (t_uint)ft_atoh(line);
		}
		return (1);
	}
	return (0);
}

static int	encoding(char *line, t_font *font)
{
	char	*str;

	str = "ENCODING";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
		{
			while (ft_isdigit(*line) == 0 && *line != '\0')
				line++;
			if (*line)
				font->glyphs[font->glyph_i].encoding = ft_atoi(line);
		}
		return (1);
	}
	return (0);
}

static int	dwidth(char *line, t_font *font)
{
	char	*str;

	str = "DWIDTH";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
			font->glyphs[font->glyph_i].dwidth[0] = (t_uint)ft_atoi(line);
		line = ft_strchr(++line, ' ');
		if (line)
			font->glyphs[font->glyph_i].dwidth[1] = (t_uint)ft_atoi(line);
		return (1);
	}
	return (0);
}

static int	boundingbox(char *line, t_font *font)
{
	char	*str;

	str = "BBX";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
			font->glyphs[font->glyph_i].bound_box[0] = (t_uint)ft_atoi(line);
		line = ft_strchr(++line, ' ');
		if (line)
			font->glyphs[font->glyph_i].bound_box[1] = (t_uint)ft_atoi(line);
		line = ft_strchr(++line, ' ');
		if (line)
			font->glyphs[font->glyph_i].offset[0] = ft_atoi(line);
		line = ft_strchr(++line, ' ');
		if (line)
			font->glyphs[font->glyph_i].offset[1] = ft_atoi(line);
		return (1);
	}
	return (0);
}

int	glyphs_branch(char *line, t_font *font)
{
	if (startchar(line, font))
		return (1);
	if (encoding(line, font))
		return (1);
	if (dwidth(line, font))
		return (1);
	if (boundingbox(line, font))
		return (1);
	return (0);
}
