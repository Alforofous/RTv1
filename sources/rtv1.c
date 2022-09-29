/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:38 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/29 17:05:11 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static draw_func	**get_image_functions(size_t count)
{
	draw_func	**f;

	f = (draw_func **)malloc(sizeof(draw_func **) * count);
	if (f == NULL)
		return (NULL);
	f[0] = &draw_image0;
	f[1] = &draw_image1;
	f[2] = &draw_image2;
	f[3] = &draw_image3;
	f[4] = &draw_image4;
	f[5] = &draw_image5;
	f[6] = &draw_image6;
	f[7] = &draw_image7;
	f[8] = &draw_image8;
	f[9] = &draw_decrement;
	f[10] = &draw_increment;
	f[11] = &draw_decrement;
	f[12] = &draw_increment;
	return (f);
}

static t_dim	*get_image_dimensions(size_t count, t_2i prop)
{
	t_dim	*dim;
	t_2i	btn;
	t_2i	btnb;

	dim = (t_dim *)malloc(sizeof(t_dim) * count);
	if (dim == NULL)
		return (NULL);
	btn.x = prop.x / 10;
	btn.y = prop.y / 5;
	btnb.x = btn.x + 3;
	btnb.y = btn.y + 3;
	dim[0] = (t_dim){prop.x * 4, SCREEN_Y, prop.x, 0, 0, 0};
	dim[1] = (t_dim){prop.x, SCREEN_Y, 0, 0, 0, 0};
	dim[2] = (t_dim){SCREEN_X / 3, SCREEN_Y / 3, SCREEN_X / 3 * 2, 0, 0, 0};
	dim[3] = (t_dim){prop.x, prop.y * 7, 0, prop.y * 3, 0, 0};
	dim[4] = (t_dim){btn.x, btn.y, prop.x - btnb.x, prop.y * 3 + 3, 0, 0};
	dim[5] = (t_dim){btn.x, btn.y, prop.x - btnb.x, prop.y * 3 - btnb.y, 0, 0};
	dim[6] = (t_dim){prop.x, prop.y * 5, 0, 0, 0, 0};
	dim[7] = (t_dim){prop.x, prop.y * 2, 0, prop.y * 8, 0, 0};
	dim[8] = (t_dim){btn.x, btn.y, prop.x - btnb.x, 0 + 3, 0, 0};
	dim[9] = (t_dim){btn.x, btn.y, 0, 0, 0, 0};
	dim[10] = dim[9];
	dim[11] = dim[9];
	dim[12] = dim[9];
	return (dim);
}

t_img	*create_images(void *mlx, size_t n, t_dim *dim, draw_func **f)
{
	t_img	*img;
	int		*prop[3];
	size_t	i;

	img = (t_img *)malloc(sizeof(t_img) * n);
	if (img == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		img[i].ptr = mlx_new_image(mlx, dim[i].width, dim[i].height);
		if (img[i].ptr == NULL)
			return (NULL);
		prop[0] = &img->bits_per_pixel;
		prop[1] = &img->line_length;
		prop[2] = &img->endian;
		img[i].addr = mlx_get_data_addr(img->ptr, prop[0], prop[1], prop[2]);
		if (img[i].addr == NULL)
			return (NULL);
		img[i].dim.width = dim[i].width;
		img[i].dim.height = dim[i].height;
		img[i].dim.x0 = dim[i].x0;
		img[i].dim.y0 = dim[i].y0;
		img[i].dim.x1 = dim[i].x0 + dim[i].width;
		img[i].dim.y1 = dim[i].y0 + dim[i].height;
		img[i].draw_func = f[i];
		i++;
	}
	return (img);
}

static void	open_screen(t_utils *utils)
{
	t_dim		*dim;
	draw_func	**funcs;

	utils->mlx = mlx_init();
	if (utils->mlx == NULL)
		close_prog(utils, "Failed to connect software to display...", -2);
	utils->win = mlx_new_window(utils->mlx, SCREEN_X, SCREEN_Y, "RTv1");
	if (utils->win == NULL)
		close_prog(utils, "Failed to open window...", -2);
	dim = get_image_dimensions(IMG_COUNT, (t_2i){SCREEN_X / 5, SCREEN_Y / 10});
	if (dim == NULL)
		close_prog(utils, "Failed to create image dimensions...", -2);
	funcs = get_image_functions(IMG_COUNT);
	if (funcs == NULL)
		close_prog(utils, "Failed to create image functions...", -2);
	utils->img = create_images(utils->mlx, IMG_COUNT, dim, funcs);
	if (utils->img == NULL)
		close_prog(utils, "Failed to create images...", -2);
	image_processing(utils, &utils->img[6], 0x006543);
	image_processing(utils, &utils->img[7], 0x000000);
	image_processing(utils, &utils->img[9], 0x000000);
	image_processing(utils, &utils->img[10], 0x000000);
	image_processing(utils, &utils->img[11], 0x000000);
	image_processing(utils, &utils->img[12], 0x000000);
	init_hooks(utils);
	utils->proj = init_proj(80.0f,
		&(t_2i){utils->img[0].dim.width, utils->img[0].dim.height},
		&(t_2f){0.1f, 1000.0f});
	mlx_do_key_autorepeatoff(utils->mlx);
}

static void	destroy_images(t_utils *utils, t_img *img)
{
	int	i;

	i = 0;
	while (i < IMG_COUNT)
	{
		mlx_destroy_image(utils->mlx, img[i].ptr);
		ft_putstr("Freed image ");
		ft_putnbr(i);
		ft_putstr("\n");
		i++;
	}
}

void	close_prog(t_utils *utils, char *exit_msg, int exit_code)
{
	if (utils->win)
		mlx_destroy_window(utils->mlx, utils->win);
	if (exit_code > -2)
		destroy_images(utils, &utils->img[0]);
	ft_putendl(exit_msg);
	exit (exit_code);
}

int	main(int argc, char **argv)
{
	t_utils	utils;

	if (argc > 2)
	{
		ft_putendl("Too many arguments.");
		return (1);
	}
	utils.objects = load_scene(argv[1]);
	init(&utils);
	open_screen(&utils);
	render_screen(&utils);
	mlx_loop(utils.mlx);
	return (0);
}
