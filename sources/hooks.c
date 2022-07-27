/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:08:09 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/27 11:02:49 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	on_destroy(void *param)
{
	t_utils	*utils;

	utils = (t_utils *)param;
	close_prog(utils, "Exited program succesfully using [X]", 1);
	return (0);
}

void *test(void *param)
{
	t_utils *utils;

	utils = (t_utils *)param;
	image_processing(utils, &utils->img, 0xFF000000);
	return (NULL);
}

int	prog_clock(void *param)
{
	t_utils		*utils;
	//pthread_t	thread_id;

	utils = (t_utils *)param;
	while (utils->density.x >= 0 && utils->density.y >= 0)
	{
		//pthread_create(&thread_id, NULL, &test, (void *)utils);
		//pthread_join(thread_id, NULL);
		if (utils->visual_rays == 0)
			image_processing(utils, &utils->img, 0xFF000000);
		utils->density.x -= 1;
	}
	if (utils->density.y > 0 && utils->density.x < 0)
	{
		utils->density.x = 9;
		utils->density.y -= 1;
	}
	if (utils->tick == 0)
	{
	}
	if (utils->tick == 100)
		utils->tick = 0;
	else
		utils->tick += 1;
	return (0);
}
