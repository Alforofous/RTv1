/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:50:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 11:09:29 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_camera(t_cam *cam)
{
	cam->rot.x = 0;
	cam->rot.y = 0;
	cam->rot.z = 0;
	cam->origin = (t_3d){0.0f, 0.0f, 0.0f};
	cam->dir.forward = (t_3d){0.0f, 0.0f, -1.0f};
}

void	init_mouse(t_utils *utils)
{
	utils->mouse.move.x = 0;
	utils->mouse.move.y = 0;
	utils->mouse.pos.x = SCREEN_X / 2;
	utils->mouse.pos.y = SCREEN_Y / 2;
	utils->mouse.button = 0;
}

static void	init_values(t_utils *utils)
{
	init_mouse(utils);
	init_camera(&utils->cam);
	utils->closest_object = NULL;
	utils->sel_object = NULL;
	utils->tick = 0;
	utils->visual_rays = 0;
	utils->render = 1;
	utils->add_object_menu = 0;
	utils->button.size = (t_2i){SCREEN_X / 40, SCREEN_Y / 25};
	utils->bitmask_key = 0;
	utils->rend_lights = -1;
	utils->shadow_bias = 0.00001f;
	utils->multiplier = 1.0f;
	utils->t_max = 10000000.0f;
	utils->pxl[0].f = &put_pixel;
	utils->hold_time = 0.08f;
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
	t_2d	z_depth;

	font_name = "cascadia_code_semi_bold-16.bdf";
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
	z_depth = (t_2d){0.1f, 1000.0f};
	utils->proj = init_proj(80.0f, &utils->img[0].dim.size, &z_depth);
	utils->rmatrix_x = init_rmatrix_x(0.0f);
	utils->rmatrix_y = init_rmatrix_y(0.0f);
	utils->rmatrix_z = init_rmatrix_z(0.0f);
}
