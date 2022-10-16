/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_bitmap_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 07:59:36 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/16 10:19:14 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

static int	bitmap(char *line, t_font *font)
{
	char	*str;
	size_t	len;
	size_t	i;

	str = "BITMAP";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		i = font->glyph_i;
		if (i >= font->glyph_count)
			return (1);
		font->glyphs[i].bitmap_line = 0;
		len = font->glyphs[i].bound_box[1];
		if (len != 0)
			font->glyphs[i].bitmap = (t_uint *)malloc(sizeof(t_uint) * len);
		if (font->glyphs[i].bitmap == NULL)
			return (-1);
		return (1);
	}
	return (0);
}

static void	fill_bitmap(char *line, t_font *font)
{
	size_t	i;
	size_t	j;

	i = font->glyph_i;
	j = font->glyphs[i].bitmap_line;
	if (j >= font->glyphs[i].bound_box[1])
		return ;
	font->glyphs[i].bitmap_size = ft_strlen(line) * 4;
	font->glyphs[i].bitmap[j] = (t_uint)ft_atoh(line);
	font->glyphs[i].bitmap_line += 1;
}

static int	endchar(char *line, t_font *font)
{
	char	*str;

	str = "ENDCHAR";

	if (font->glyph_i >= font->glyph_count)
		return (2);
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		font->glyph_i++;
		return (1);
	}
	return (0);
}

int	bitmap_branch(char *line, t_font *font)
{
	int			ret;
	static int	bitmap_toggle;

	if (endchar(line, font))
	{
		bitmap_toggle = 0;
		return (1);
	}
	if (bitmap_toggle == 1)
	{
		fill_bitmap(line, font);
		return (1);
	}
	ret = bitmap(line, font);
	if (ret == 1)
		bitmap_toggle = 1;
	return (ret);
}
