/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:15:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/21 16:11:30 by bbeltran         ###   ########.fr       */
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
	int				y;

	color = 0x00FF0000;
	draw_height = HEIGHT / cub->cam.dist;
	y = HEIGHT / 2 - draw_height / 2;
	if (y < 0)
		y = 0;
	draw_end = draw_height / 2 + HEIGHT / 2;
	if (draw_end < 0)
		draw_end = HEIGHT - 1;
	while (y < draw_end)
	{
		mlx_pixel_put(cub->mlx.connect, cub->mlx.window, *x, y, color);
		y++;
	}
}

void	raycaster(t_cub *cub)
{
	int			x;
	t_cam		*cam;
	t_player	player;

	x = 0;
	cam = &cub->cam;
	player = cub->player;
	while (x < WIDTH)
	{
		cam->stepX = 0;
		cam->stepY = 0;
		cam->wall_hit = 0;
		cam->cam_x = ((2 * x) / (double)WIDTH) - 1;
		cam->rayDir.x = player.dir.x + cam->plane.x * cam->cam_x;
		cam->rayDir.y = player.dir.y + cam->plane.y * cam->cam_x;
		if (!cam->rayDir.x)
			cam->deltaDistX = 1e30;
		else
			cam->deltaDistX = fabs(1 / cam->rayDir.x);
		if (!cam->rayDir.y)
			cam->deltaDistY = 1e30;
		else
			cam->deltaDistY = fabs(1 / cam->rayDir.y);
		cam->mapX = (player.pos.x / TILE_SIZE);
		cam->mapY = (player.pos.y / TILE_SIZE);
		if (cam->rayDir.x < 0)
		{
			cam->stepX = -1;
			cam->sideDistX = ((player.pos.x / TILE_SIZE) - cam->mapX) * cam->deltaDistX;
		}
		else
		{
			cam->stepX = 1;
			cam->sideDistX = (cam->mapX + 1 - (player.pos.x / TILE_SIZE)) * cam->deltaDistX;
		}
		if (cam->rayDir.y < 0)
		{
			cam->stepY = -1;
			cam->sideDistY = ((player.pos.y / TILE_SIZE) - cam->mapY) * cam->deltaDistY;
		}
		else
		{
			cam->stepY = 1;
			cam->sideDistY = (cam->mapY + 1 - (player.pos.y / TILE_SIZE)) * cam->deltaDistY;
		}
		while (!cam->wall_hit)
		{
			if (cam->sideDistX < cam->sideDistY)
			{
				cam->hit_type = 0;
				cam->sideDistX += cam->deltaDistX;
				cam->mapX += cam->stepX;
			}
			else
			{
				cam->hit_type = 1;
				cam->sideDistY += cam->deltaDistY;
				cam->mapY += cam->stepY;
			}
			if (cub->map[cam->mapY][cam->mapX] && cub->map[cam->mapY][cam->mapX] == '1')
				cam->wall_hit = 1;
		}
		if (cam->hit_type == 0)
			cam->dist = cam->sideDistX - cam->deltaDistX;
		else
			cam->dist = cam->sideDistY - cam->deltaDistY;
		paint_ray(cub, &x);
		x++;
	}
}

void	draw_screen(t_cub *cub)
{
	paint_background(cub);
	raycaster(cub);
}
