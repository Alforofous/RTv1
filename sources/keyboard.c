/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/28 12:01:44 by dmalesev         ###   ########.fr       */
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

void	fov_keys(t_utils *utils, int key)
{
	if (key == NUM_PLUS && utils->proj.fov < 120)
		utils->proj.fov += 1;
	else if (key == NUM_MINUS && utils->proj.fov > 10)
		utils->proj.fov -= 1;
	utils->proj.fov_rad = (float)(1 / tan(utils->proj.fov / 2 / 180 * PI));
}

/*left right down up*/
void	arrow_keys(t_utils *utils, int key)
{
	if (key == UP || key == W)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.forward);
	if (key == LEFT || key == A)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.left);
	if (key == DOWN || key == S)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.back);
	if (key == RIGHT || key == D)
		utils->cam.origin = add_vectors(&utils->cam.origin,
			&utils->cam.dir.right);
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
	fov_keys(utils, key);
	toggle_keys(utils, key);
	render_screen(utils);
	return (0);
}
