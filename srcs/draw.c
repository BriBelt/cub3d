/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:15:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/23 16:23:46 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_background(t_cub *cub, int height, int end, int x)
{
	int				y;
	t_mlx			*mlx;
	int				start;
	unsigned int	color;
	t_img			frame;

	y = 0;
	mlx = &cub->mlx;
	start = cub->start;
	frame = mlx->frame;
	while (y < start)
	{
		frame.addr[y * WIDTH + x] = cub->cceiling;
		y++;
	}
	while (start < end)
	{
		color = get_tex_color(cub, start, height);
		frame.addr[start * WIDTH + x] = color;
		start++;
	}
	y = start;
	while (y < HEIGHT)
	{
		frame.addr[y * WIDTH + x] = cub->cfloor;
		y++;
	}
}

void	paint_ray(t_cub *cub, int *x)
{
	double			draw_height;
	double			draw_end;
	int				start;

	get_texX(cub, *cub->textures);
	draw_height = HEIGHT / cub->cam.dist;
	start = HEIGHT / 2 - draw_height / 2;
	if (start < 0)
		start = 0;
	draw_end = draw_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	cub->start = start;
	load_background(cub, (int)draw_height, (int)draw_end, *x);
}

void	draw_screen(t_cub *cub)
{
	if (cub->mlx.frame.img)
		mlx_destroy_image(cub->mlx.connect, cub->mlx.frame.img);
	create_image(cub->mlx, &cub->mlx.frame);
	raycaster(cub);
	mlx_put_image_to_window(cub->mlx.connect, cub->mlx.window,
			cub->mlx.frame.img, 0, 0);
}
