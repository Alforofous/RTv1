/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:38 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/15 11:06:09 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	crt_img(t_utils *utils, t_img *img, t_4i *d, void (*f)(t_utils *u))
{
	img->dim.width = d->a;
	img->dim.height = d->b;
	img->dim.x0 = d->c;
	img->dim.y0 = d->d;
	img->dim.x1 = d->c + img->dim.width;
	img->dim.y1 = d->d + img->dim.height;
	img->next = NULL;
	img->draw_func = f;
	img->ptr = mlx_new_image(utils->mlx, d->a, d->b);
	if (!img->ptr)
		close_prog(utils, "Failed to create an image...", -1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static void	open_screen(t_utils *utils)
{
	utils->mlx = mlx_init();
	if (!utils->mlx)
		close_prog(utils, "Failed to connect software to display...", -2);
	utils->win = mlx_new_window(utils->mlx, SCREEN_X, SCREEN_Y, "RTv1");
	if (!utils->win)
		close_prog(utils, "Failed to open window...", -2);
	crt_img(utils, &utils->img, &(t_4i){SCREEN_X / 5 * 4, SCREEN_Y,
		SCREEN_X / 5, 0}, &draw_image1);
	crt_img(utils, &utils->img2, &(t_4i){SCREEN_X / 5, SCREEN_Y, 0, 0},
		&draw_image2);
	utils->img.next = &utils->img2;
	init_hooks(utils);
}

static void	destroy_images(t_utils *utils, t_img *images)
{
	while (images)
	{
		mlx_destroy_image(utils->mlx, images->ptr);
		ft_putstr("Freed image sized: [");
		ft_putnbr(images->dim.width);
		ft_putstr(" X ");
		ft_putnbr(images->dim.height);
		ft_putendl("]");
		images->ptr = NULL;
		images = images->next;
	}
}

void	close_prog(t_utils *utils, char *exit_msg, int exit_code)
{
	if (utils->win)
		mlx_destroy_window(utils->mlx, utils->win);
	if (utils->img.ptr && exit_code > -2)
		destroy_images(utils, &utils->img);
	ft_putendl(exit_msg);
	exit (exit_code);
}

int	main(void)
{
	t_utils	utils;

	init(&utils);
	open_screen(&utils);
	load_obj("rend_obj/cube_simple.obj", &utils.objects.cube);
	load_obj("rend_obj/teapot.obj", &utils.objects.teapot);
	load_obj("rend_obj/sphere.obj", &utils.objects.sphere);
	load_obj("rend_obj/monkey.obj", &utils.objects.monkey);
	load_obj("rend_obj/abstract.obj", &utils.objects.abstract);
	print_obj_params(&utils.objects.cube);
	render_screen(&utils);
	mlx_loop(utils.mlx);
	return (0);
}
