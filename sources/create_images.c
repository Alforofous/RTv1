/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:19:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/30 16:46:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	get_image_sizes(t_img *img)
{
	t_2i	button;
	t_2i	sidebar;

	button.x = SCREEN_X / 50;
	button.y = SCREEN_Y / 30;
	sidebar.x = SCREEN_X * 20 / 100;
	sidebar.y = SCREEN_Y;
	img[0].dim.size = (t_2i){SCREEN_X * 80 / 100, SCREEN_Y};
	img[1].dim.size = (t_2i){sidebar.x, sidebar.y};
	img[2].dim.size = (t_2i){SCREEN_X * 40 / 100, SCREEN_X * 40 / 100};
	img[3].dim.size = (t_2i){sidebar.x, sidebar.y * 70 / 100};
	img[4].dim.size = button;
	img[5].dim.size = button;
	img[6].dim.size = (t_2i){sidebar.x, sidebar.y * 50 / 100};
	img[7].dim.size = (t_2i){sidebar.x, sidebar.y * 20 / 100};
	img[8].dim.size = button;
	img[9].dim.size = button;
	img[10].dim.size = button;
	img[11].dim.size = button;
	img[12].dim.size = button;
}

static void	get_image_positions(t_img *img, size_t count)
{
	t_2i	button;
	t_2i	sidebar;
	t_2i	b_pos;
	size_t	i;
	int		offset;

	button.x = SCREEN_X / 50;
	button.y = SCREEN_Y / 30;
	offset = (button.x + button.y) / 5;
	sidebar.x = SCREEN_X * 20 / 100;
	sidebar.y = SCREEN_Y;
	img[0].dim.start = (t_2i){sidebar.x, 0};
	img[1].dim.start = (t_2i){0, 0};
	img[2].dim.start = (t_2i){SCREEN_X - img[2].dim.size.x, 0};
	img[3].dim.start = (t_2i){0, sidebar.y * 30 / 100};
	b_pos = (t_2i){sidebar.x - button.x - offset, img[3].dim.start.y};
	img[4].dim.start = (t_2i){b_pos.x, b_pos.y + offset};
	img[5].dim.start = (t_2i){b_pos.x, b_pos.y - button.y - offset};
	img[6].dim.start = (t_2i){0, 0};
	img[7].dim.start = (t_2i){0, sidebar.y * 80 / 100};
	img[8].dim.start = (t_2i){b_pos.x, 0 + offset};
	img[9].dim.start = (t_2i){0, 0};
	img[10].dim.start = img[9].dim.start;
	img[11].dim.start = img[9].dim.start;
	img[12].dim.start = img[9].dim.start;
	i = 0;
	while (i < count)
	{
		img[i].dim.end.x = img[i].dim.start.x + img[i].dim.size.x;
		img[i].dim.end.y = img[i].dim.start.y + img[i].dim.size.y;
		i++;
	}
}

static void	get_image_functions(t_img *img)
{
	img[0].draw_func = &draw_image0;
	img[1].draw_func = &draw_image1;
	img[2].draw_func = &draw_image2;
	img[3].draw_func = &draw_image3;
	img[4].draw_func = &draw_image4;
	img[5].draw_func = &draw_image5;
	img[6].draw_func = &draw_image6;
	img[7].draw_func = &draw_image7;
	img[8].draw_func = &draw_image8;
	img[9].draw_func = &draw_decrement;
	img[10].draw_func = &draw_increment;
	img[11].draw_func = &draw_decrement;
	img[12].draw_func = &draw_increment;
}

t_img	*free_images(void * mlx, t_img *img, int i)
{
	while (--i >= 0)
	{
		if (img[i].ptr != NULL)
			mlx_destroy_image(mlx, img[i].ptr);
	}
	if (img !=NULL)
		free(img);
	return (NULL);
}

t_img	*create_images(void *mlx, size_t count)
{
	t_img	*img;
	int		*prop[3];
	size_t	i;

	img = (t_img *)malloc(sizeof(t_img) * count);
	ft_bzero(img, sizeof(t_img));
	if (img == NULL)
		return (NULL);
	i = 0;
	get_image_sizes(img);
	get_image_positions(img, count);
	while (i < count)
	{
		if (img[i].dim.size.x <= 0 || img[i].dim.size.y <= 0)
			return (free_images(mlx, img, (int)i));
		img[i].ptr = mlx_new_image(mlx, img[i].dim.size.x, img[i].dim.size.y);
		if (img[i].ptr == NULL)
			return (free_images(mlx, img, (int)i));
		prop[0] = &img[i].bits_per_pixel;
		prop[1] = &img[i].line_length;
		prop[2] = &img[i].endian;
		img[i].addr = mlx_get_data_addr(img[i].ptr, prop[0], prop[1], prop[2]);
		i++;
	}
	get_image_functions(img);
	return (img);
}