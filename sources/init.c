/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/11 11:39:54 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_camera(t_utils *utils)
{
	utils->rot.x = 0;
	utils->rot.y = 0;
	utils->rot.z = 0;
	utils->cam.origin = (t_3f){0.0f, 0.0f, 0.0f};
	utils->cam.dir.forward = (t_3f){0.0f, 0.0f, -1.0f};
}

void	init_mouse(t_utils *utils)
{
	utils->mouse.move_x = 0;
	utils->mouse.move_y = 0;
	utils->mouse.zoom = 20;
	utils->mouse.x = SCREEN_X / 2;
	utils->mouse.y = SCREEN_Y / 2;
	utils->mouse.button = 0;
}

static void	init_values(t_utils *utils)
{
	init_mouse(utils);
	init_camera(utils);
	utils->closest_object = NULL;
	utils->sel_object = NULL;
	utils->tick = 0;
	utils->visual_rays = 0;
	utils->render = -1;
	utils->elapsed_time = 0;
	clock_gettime(CLOCK_MONOTONIC, &utils->time);
	utils->add_object_menu = 0;
	utils->button.size = (t_2i){SCREEN_X / 40, SCREEN_Y / 25};
	utils->bitmask_key = 0;
	utils->light_render = -1;
	utils->shadow_bias = 0.001f;
	utils->multiplier = 1.0f;
	utils->t_max = 10000000.0f;
	utils->pxl[0].f = &put_pixel;
}

static void	draw_images(t_utils *utils, t_img *img, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		utils->curr_img = &img[i];
		utils->pxl[0].param = &img[i];
		img[i].draw_func(utils);
		i++;
	}
}

void	init(t_utils *utils)
{
	char	*font_name;
	t_2f	z_depth;

	font_name = "libraries/dm_bdf_render/examples/bdf_files/cascadia_code.bdf";
	ft_bzero(utils, sizeof(t_utils));
	close_prog(utils, "Initialising close_prog function.", 42);
	init_mlx(utils);
	init_values(utils);
	utils->img = create_images(utils->mlx, IMG_COUNT);
	if (utils->img == NULL)
		close_prog(NULL, "Failed to create images...", -2);
	utils->font = load_font(font_name);
	if (utils->font == NULL)
		close_prog(NULL, "Failed to load font...", -2);
	utils->pxl[0].font = utils->font;
	draw_images(utils, utils->img, IMG_COUNT);
	z_depth = (t_2f){0.1f, 1000.0f};
	utils->proj = init_proj(80.0f, &utils->img[0].dim.size, &z_depth);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
