/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:15:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/16 17:57:46 by bbeltran         ###   ########.fr       */
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

void	raycaster(t_cub *cub)
{
	int			x;
	t_cam		cam;
	t_player	player;

	x = 0;
	cam = cub->cam;
	player = cub->player;
	while (x < WIDTH)
	{
		cam.cam_x = 2x / WIDTH - 1;
		cam.rayDir.x = player.dir.x + cam.plane.x * cam.cam_x;
		cam.rayDir.y = player.dir.y + cam.plane.y * cam.cam_x;
		cam.mapX = (int)(player.pos.x / TILE_SIZE);
		cam.mapY = (int)(player.pos.y / TILE_SIZE);
		cam.deltaDistX = fabs(1 / cam.rayDir.x);
		cam.deltaDistY = fabs(1 / cam.rayDir.y);
		if (cam.rayDir.x < 0)
		{
			cam.stepX = -1;
			cam.sideDistX = cam.mapX - (player.pos.x / TILE_SIZE) * cam.deltaDistX;
		}
		else
		{
			cam.stepX = 1;
			cam.sideDistX = cam.mapX + 1 - (player.pos.x / TILE_SIZE) * cam.deltaDistX;
		}
		if (cam.rayDir.y < 0)
		{
			cam.stepY = -1;
			cam.sideDistY = cam.mapY - (player.pos.y / TILE_SIZE) * cam.deltaDistY;
		}
		else
		{
			cam.stepY = 1;
			cam.sideDistY = cam.mapY + 1 - (player.pos.y / TILE_SIZE) * cam.deltaDistY;
		}
		while (!cam.wall_hit)
		{
			if (cam.sideDistX < cam.sideDistY)
			{
				cam.hit_type = 0;
				cam.sideDistX += cam.deltaDistX;
				cam.mapX += cam.stepX;
			}
			else
			{
				cam.hit_type = 1;
				cam.sideDistY += cam.deltaDistY;
				cam.mapY += cam.stepY;
			}
			if (cub->map[cam.mapY][cam.mapX] != '0')
				cam.wall_hit = 1;
		}
		if (cam.hit_type == 0)
			cam.dist = cam.sideDistX - cam.deltaDistX;
		else
			cam.dist = cam.sideDistY - cam.deltaDistY;
		x++;
	}
}

void	draw_screen(t_cub *cub)
{
	paint_background(cub);
	raycaster(cub);
}
