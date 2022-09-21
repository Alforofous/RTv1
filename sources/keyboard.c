/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/21 13:46:01 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*Keys that toggle option on or off*/
static void	toggle_keys(t_utils *utils, int key)
{
	if (key == DOT)
		utils->bitmask_key ^= BITMASK_DOT;
	else if (key == T)
		utils->bitmask_key ^= BITMASK_T;
	else if (key == R)
		utils->bitmask_key ^= BITMASK_R;
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
		utils->bitmask_key ^= BITMASK_DEL;
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
	camera(utils, key);
	object(utils, key);
	fov_keys(utils, key);
	toggle_keys(utils, key);
	printf("BITMAKS: %ld\n", utils->bitmask_key);
	utils->add_object_popup = 0;
	return (0);
}

int	key_up(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	camera(utils, key);
	object(utils, key);
	fov_keys(utils, key);
	toggle_keys(utils, key);
	printf("BITMAKS: %ld\n", utils->bitmask_key);
	utils->add_object_popup = 0;
	return (0);
}
