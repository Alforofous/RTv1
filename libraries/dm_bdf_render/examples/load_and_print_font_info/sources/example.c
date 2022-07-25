/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:07:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 08:34:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dm_bdf_render.h"

int	main(int argc, char **argv)
{
	t_font	*font;

	if (argc != 2)
	{
		ft_putstr("Usage: <filename.bdf>\n");
		return (1);
	}
	font = load_font(argv[1]);
	if (font == NULL)
	{
		ft_putstr("Failed to malloc font's parameters.\n");
		return (1);
	}
	print_font_info(font);
	free_font(&font);
	return (0);
}
