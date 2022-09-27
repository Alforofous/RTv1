/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 13:39:06 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Keys that toggle option on or off*/
static void	toggle_keys(t_utils *utils, int key)
{
	if (key == DOT)
		utils->visual_rays += 1;
	else if (key == T)
		init_camera(utils);
	else if (key == R)
		utils->render *= -1;
	else if (key == L)
		utils->light_render *= -1;
	else
		return ;
	if (utils->visual_rays == 3)
		utils->visual_rays = 0;
	render_screen(utils);
}

static void	fov_keys(t_utils *utils, int key)
{
	if (key == NUM_PLUS)
		utils->bitmask_key ^= BITMASK_NUM_PLUS;
	else if (key == NUM_MINUS)
		utils->bitmask_key ^= BITMASK_NUM_MINUS;
}

static void	object(t_utils *utils, int key)
{
	if (key == UP)
		utils->bitmask_key ^= BITMASK_UP;
	else if (key == LEFT)
		utils->bitmask_key ^= BITMASK_LEFT;
	else if (key == DOWN)
		utils->bitmask_key ^= BITMASK_DOWN;
	else if (key == RIGHT)
		utils->bitmask_key ^= BITMASK_RIGHT;
	else if (key == DEL || key == BACKSPACE)
		delete_sel_object(utils, &utils->objects);
}

static void	camera(t_utils *utils, int key)
{
	if (key == W)
		utils->bitmask_key ^= BITMASK_W;
	else if (key == A)
		utils->bitmask_key ^= BITMASK_A;
	else if (key == S)
		utils->bitmask_key ^= BITMASK_S;
	else if (key == D)
		utils->bitmask_key ^= BITMASK_D;
	else if (key == SPACE)
		utils->bitmask_key ^= BITMASK_SPACE;
	else if (key == L_SHIFT)
		utils->bitmask_key ^= BITMASK_L_SHIFT;
}

int	key_down(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	ft_putnbr(key);
	camera(utils, key);
	if (utils->sel_object != NULL)
		object(utils, key);
	fov_keys(utils, key);
	toggle_keys(utils, key);
	printf("BITMAKS: %ld\n", utils->bitmask_key);
	utils->add_object_menu = 0;
	return (0);
}

int	key_up(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	camera(utils, key);
	if (utils->sel_object != NULL)
		object(utils, key);
	fov_keys(utils, key);
	printf("BITMAKS: %ld\n", utils->bitmask_key);
	utils->add_object_menu = 0;
	return (0);
}
