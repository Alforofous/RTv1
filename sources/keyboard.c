/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/10 16:08:58 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Keys that toggle option on or off*/
void	toggle_keys(t_utils *utils, int key)
{
	if (key == DOT)
		utils->reference *= -1;
	if (key == T)
		utils->visual_rays *= -1;
}

/*left right down up*/
void	arrow_keys(t_utils *utils, int key)
{
	utils += 0;
	key += 0;
}

int	key_down(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	ft_putnbr(key);
	if (key == ESC)
		close_prog(utils, "Exited program succesfully using ESC.", 1);
	if (key == SPACE)
		utils->rot.z += 1;
	arrow_keys(utils, key);
	toggle_keys(utils, key);
	render_screen(utils);
	return (0);
}
