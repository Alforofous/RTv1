/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_font_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:20:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/23 14:27:42 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

void	print_font_params(t_font *font)
{
	if (font == NULL)
		return ;
	ft_putstr("\e[34mFONTBOUNDINGBOX:\e[0m ");
	ft_putnbr((int)font->bound_box[0]);
	ft_putchar(' ');
	ft_putnbr((int)font->bound_box[1]);
	ft_putchar(' ');
	ft_putnbr(font->offset[0]);
	ft_putchar(' ');
	ft_putnbr(font->offset[1]);
	ft_putchar('\n');
	ft_putchar('\n');
}

void	print_font_properties(t_prop *properties)
{
	if (properties == NULL)
		return ;
	ft_putstr("\e[36mFONT_ASCENT:\e[0m ");
	ft_putnbr(properties->ascent);
	ft_putchar('\n');
	ft_putstr("\e[36mFONT_DESCENT:\e[0m ");
	ft_putnbr(properties->descent);
	ft_putchar('\n');
	ft_putstr("\e[36mDEFAULT_CHAR:\e[0m ");
	ft_putchar((char)properties->default_char);
	ft_putchar('\n');
	ft_putchar('\n');
}

void	print_glyph_info(t_glyph *glyph)
{
	if (glyph == NULL)
		return ;
	ft_putstr("\e[31mUNICODE:\e[0m (real in hex)");
	ft_putnbr((int)glyph->unicode);
	ft_putchar('\n');
	ft_putstr("\e[31mENCODING:\e[0m ");
	ft_putnbr(glyph->encoding);
	ft_putchar('\n');
	ft_putstr("\e[31mDWIDTH:\e[0m ");
	ft_putnbr((int)glyph->dwidth[0]);
	ft_putchar(' ');
	ft_putnbr((int)glyph->dwidth[1]);
	ft_putchar('\n');
	ft_putstr("\e[31mBBX:\e[0m ");
	ft_putnbr((int)glyph->bound_box[0]);
	ft_putchar(' ');
	ft_putnbr((int)glyph->bound_box[1]);
	ft_putchar(' ');
	ft_putnbr(glyph->offset[0]);
	ft_putchar(' ');
	ft_putnbr(glyph->offset[1]);
	ft_putchar(' ');
	ft_putchar('\n');
	ft_putchar('\n');
}

void	print_glyphs_bitmap(t_glyph *glyph)
{
	size_t	j;

	j = 0;
	if (glyph == NULL)
		return ;
	while (j < glyph->bound_box[1])
	{
		ft_putnbr((int)glyph->bitmap[j]);
		ft_putchar('\n');
		j++;
	}
}

void	print_font_info(t_font *font)
{
	size_t	i;

	if (font == NULL)
		return ;
	ft_putstr("-------------------------------------------------\n");
	print_font_params(font);
	print_font_properties(&font->properties);
	i = 0;
	while (i < font->glyph_count)
	{
		print_glyph_info(&font->glyphs[i]);
		ft_putstr("\e[33mBITMAP:\e[0m (real in hex)");
		print_glyphs_bitmap(&font->glyphs[i]);
		ft_putchar('\n');
		i++;
	}
	ft_putstr("-------------------------------------------------\n");
}
