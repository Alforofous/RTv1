/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bdf_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:07:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:53:28 by dmalesev         ###   ########.fr       */
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
	return (1);
}

void	free_font(t_font **font)
{
	if (*font == NULL)
		return ;
	while ((*font)->glyph_i >= (*font)->glyph_count)
	{
		(*font)->glyph_i -= 1;
	}
	while ((*font)->glyph_i > 0)
	{
		if ((*font)->glyphs[(*font)->glyph_i].bitmap != NULL)
			free((*font)->glyphs[(*font)->glyph_i].bitmap);
		(*font)->glyph_i -= 1;
	}
	if ((*font)->glyphs[(*font)->glyph_i].bitmap != NULL)
		free((*font)->glyphs[(*font)->glyph_i].bitmap);
	if ((*font)->glyphs != NULL)
		free((*font)->glyphs);
	free(*font);
	*font = NULL;
}

static int	get_font_info(char *path, t_font *font)
{
	int		fd;
	int		ret[2];
	char	*line;

	ret[0] = 1;
	ret[1] = 1;
	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (ret[0] > 0 && ret[1] >= 0)
	{
		line = NULL;
		ret[0] = get_next_line(fd, &line);
		if (ret[0] == -1)
			break ;
		if (ret[0] > 0)
			ret[1] = font_branch(line, font);
		if (line != NULL)
			free(line);
	}
	close(fd);
	return (ret[1]);
}

t_font	*load_font(char *path)
{
	t_font	*font;

	font = (t_font *)malloc(sizeof(t_font));
	if (font == NULL)
		return (NULL);
	ft_bzero(font, sizeof(t_font));
	font->properties.default_char = 63;
	font->glyph_count = ft_strs_in_file(path, "STARTCHAR");
	if (font->glyph_count <= 0)
	{
		free(font);
		return (NULL);
	}
	font->glyphs = (t_glyph *)malloc(sizeof(t_glyph) * font->glyph_count);
	if (font->glyphs == NULL)
	{
		free(font);
		return (NULL);
	}
	if (get_font_info(path, font) == -1)
	{
		free_font(&font);
		return (NULL);
	}
	return (font);
}
