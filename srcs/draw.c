/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:15:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/22 15:56:26 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	paint_background(t_cub *cub)
{
	int				x;
	int				y;
	unsigned int	b_color;

	y = 0;
	b_color = 0x00000000;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(cub->mlx.connect, cub->mlx.window, x, y, b_color);
			x++;
		}
		y++;
	}
}

void	paint_ray(t_cub *cub, int *x)
{
	double			draw_height;
	double			draw_end;
	unsigned int	color;
	int				start;
	int				y;

	get_texX(cub);
	draw_height = HEIGHT / cub->cam.dist;
	start = HEIGHT / 2 - draw_height / 2;
	if (start < 0)
		start = 0;
	draw_end = draw_height / 2 + HEIGHT / 2;
	if (draw_end < 0)
		draw_end = HEIGHT - 1;
	y = start;
	while (y < draw_end)
	{
		color = get_tex_color(cub, y, draw_height);
		mlx_pixel_put(cub->mlx.connect, cub->mlx.window, *x, y, color);
		y++;
	}
}

void	draw_screen(t_cub *cub)
{
	paint_background(cub);
	raycaster(cub);
}
