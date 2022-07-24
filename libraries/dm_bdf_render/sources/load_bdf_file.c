/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bdf_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:07:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/24 20:41:24 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

static int	font_branch(char *line, t_font *font)
{
	int	ret;

	ret = bitmap_branch(line, font);
	if (ret == 1 || ret == -1)
		return (ret);
	ret = params_branch(line, font);
	if (ret == 1 || ret == -1)
		return (ret);
	ret = properties_branch(line, font);
	if (ret == 1 || ret == -1)
		return (ret);
	ret = glyphs_branch(line, font);
	if (ret == 1 || ret == -1)
		return (ret);
	return (0);
}

void	free_font(t_font *font)
{
	if (font == NULL)
		return ;
	while (font->glyph_i != 0)
	{
		if (font->glyphs[font->glyph_i].bitmap != NULL)
			free(font->glyphs[font->glyph_i].bitmap);
		font->glyph_i--;
	}
	if (font->glyphs[font->glyph_i].bitmap != NULL)
		free(font->glyphs[font->glyph_i].bitmap);
	if (font->glyphs != NULL)
		free(font->glyphs);
	free(font);
}

static int	get_font_info(char *path, t_font *font)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-1);
		if (line)
		{
			if (font_branch(line, font) == -1)
			{
				free_font(font);
				free(line);
				return (-1);
			}
		}
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}

t_font	*load_font(char *path)
{
	t_font	*font;

	font = (t_font *)malloc(sizeof(t_font));
	if (font == NULL)
		return (NULL);
	font->glyph_i = 0;
	font->properties.default_char = 63;
	font->glyph_count = ft_strs_in_file(path, "STARTCHAR");
	font->glyphs = (t_glyph *)malloc(sizeof(t_glyph) * font->glyph_count);
	if (font->glyphs == NULL)
	{
		free(font);
		return (NULL);
	}
	if (get_font_info(path, font) == -1)
		return (NULL);
	return (font);
}
