/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:38 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/22 12:17:38 by dmalesev         ###   ########.fr       */
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
	crt_img(utils, &utils->img1, &(t_4i){SCREEN_X / 5 * 4, SCREEN_Y,
		SCREEN_X / 5, 0}, &draw_image1);
	crt_img(utils, &utils->img2, &(t_4i){SCREEN_X / 5, SCREEN_Y, 0, 0},
		&draw_image2);
	crt_img(utils, &utils->img3, &(t_4i){SCREEN_X / 4, SCREEN_Y / 4,
		SCREEN_X / 4 * 3, 0}, &draw_image3);
	crt_img(utils, &utils->img4, &(t_4i){SCREEN_X / 5, SCREEN_Y / 10 * 7,
		0, SCREEN_Y / 10 * 3}, &draw_image4);
	crt_img(utils, &utils->img5, &(t_4i){SCREEN_X / 5 / 10, SCREEN_Y / 10 * 3 / 10,
		SCREEN_X / 5 - SCREEN_X / 5 / 10 - (int)(SCREEN_Y / 10 * 3 * 0.02), SCREEN_Y / 10 * 3 + (int)(SCREEN_Y / 10 * 3 * 0.02)}, &draw_image5);
	crt_img(utils, &utils->img6, &(t_4i){SCREEN_X / 5 / 10, SCREEN_Y / 10 * 3 / 10,
		SCREEN_X / 5 - SCREEN_X / 5 / 10 - (int)(SCREEN_Y / 10 * 3 * 0.02), (int)((float)SCREEN_Y * 0.27)}, &draw_image6);
	crt_img(utils, &utils->img7, &(t_4i){SCREEN_X / 5, SCREEN_Y / 10 * 5,
		0, 0}, &draw_image7);
	crt_img(utils, &utils->img8, &(t_4i){SCREEN_X / 5, SCREEN_Y / 10 * 2, 0, SCREEN_Y / 10 * 8},
		&draw_image8);
	crt_img(utils, &utils->img9, &(t_4i){SCREEN_X / 5 / 10, SCREEN_Y / 10 * 3 / 10,
		SCREEN_X / 5 - SCREEN_X / 5 / 10 - (int)(SCREEN_Y / 10 * 3 * 0.02), 0 + (int)((float)SCREEN_Y / 10 * 3 / 10 * 0.02)}, &draw_image9);
	utils->img1.next = &utils->img2;
	utils->img2.next = &utils->img3;
	utils->img3.next = &utils->img4;
	utils->img4.next = &utils->img5;
	utils->img5.next = &utils->img6;
	utils->img6.next = &utils->img7;
	utils->img7.next = &utils->img8;
	utils->img8.next = &utils->img9;
	image_processing(utils, &utils->img7, 0x006543);
	image_processing(utils, &utils->img8, 0x000000);
	init_hooks(utils);
	utils->proj = init_proj(80.0f,
		&(t_2i){utils->img1.dim.width, utils->img1.dim.height},
		&(t_2f){0.1f, 1000.0f});
	mlx_do_key_autorepeatoff(utils->mlx);
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
	if (utils->img1.ptr && exit_code > -2)
		destroy_images(utils, &utils->img1);
	ft_putendl(exit_msg);
	exit (exit_code);
}

int	main(void)
{
	t_utils	utils;

	init(&utils);
	open_screen(&utils);
	render_screen(&utils);
	mlx_loop(utils.mlx);
	return (0);
}
