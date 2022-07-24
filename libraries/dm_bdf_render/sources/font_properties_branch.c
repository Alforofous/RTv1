/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_properties_branch.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:49:48 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/23 13:53:21 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

static int	font_ascent(char *line, t_font *font)
{
	char	*str;

	str = "FONT_ASCENT";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
			font->properties.ascent = ft_atoi(line);
		return (1);
	}
	return (0);
}

static int	font_descent(char *line, t_font *font)
{
	char	*str;

	str = "FONT_DESCENT";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
			font->properties.descent = ft_atoi(line);
		return (1);
	}
	return (0);
}

static int	default_char(char *line, t_font *font)
{
	char	*str;

	str = "DEFAULT_CHAR";
	if (ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
	{
		line = ft_strchr(line, ' ');
		if (line)
			font->properties.default_char = ft_atoi(line);
		return (1);
	}
	return (0);
}

int	properties_branch(char *line, t_font *font)
{
	if (font_ascent(line, font))
		return (1);
	if (font_descent(line, font))
		return (1);
	if (default_char(line, font))
		return (1);
	return (0);
}
