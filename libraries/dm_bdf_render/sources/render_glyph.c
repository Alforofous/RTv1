/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_glyph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:03:30 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/24 18:45:18 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

t_glyph	*find_matching_encoding(int encoding, t_font *font)
{
	size_t	i;

	i = 0;
	while (i < font->glyph_count)
	{
		if (encoding == font->glyphs[i].encoding)
			return (&font->glyphs[i]);
		i++;
	}
	return (NULL);
}

static void	draw_glyph(t_glyph *glyph, t_pxl *pxl, t_2i *crds, t_font *font)
{
	t_uint	bitmask;
	t_uint	bit_reader;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < glyph->bound_box[1])
	{
		bitmask = ft_reverse_bits(glyph->bitmap[i], (int)glyph->bitmap_size);
		bit_reader = (t_uint)(1);
		j = 0;
		while (j < 31)
		{
			if ((bitmask & bit_reader) == bit_reader)
			{
				pxl->f(crds->x + (int)j + glyph->offset[0],
					crds->y + (int)i + (int)font->properties.ascent
					- (int)glyph->bound_box[1] - glyph->offset[1],
					0xFF0000, (void *)pxl->param);
			}
			bit_reader <<= 1;
			j++;
		}
		i++;
	}
}

t_2i	render_glyph(int encoding, t_pxl *pxl, t_2i *crds, t_font *font)
{
	t_glyph	*glyph;

	glyph = find_matching_encoding(encoding, font);
	if (glyph == NULL)
		glyph = find_matching_encoding(font->properties.default_char, font);
	if (glyph == NULL)
		return (*crds);
	draw_glyph(glyph, pxl, crds, font);
	crds->x += (int)glyph->dwidth[0];
	return (*crds);
}
