/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:43:18 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/23 16:21:23 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_calc(t_player player, t_cam *cam)
{
	if (cam->rayDir.x < 0)
	{
		cam->stepX = -1;
		cam->sideDistX = ((player.pos.x / TILE_SIZE) - cam->mapX)
			* cam->deltaDistX;
	}
	else
	{
		cam->stepX = 1;
		cam->sideDistX = (cam->mapX + 1 - (player.pos.x / TILE_SIZE))
			* cam->deltaDistX;
	}
	if (cam->rayDir.y < 0)
	{
		cam->stepY = -1;
		cam->sideDistY = ((player.pos.y / TILE_SIZE) - cam->mapY)
			* cam->deltaDistY;
	}
	else
	{
		cam->stepY = 1;
		cam->sideDistY = (cam->mapY + 1 - (player.pos.y / TILE_SIZE))
			* cam->deltaDistY;
	}
}

void	throw_ray(t_cub *cub, t_cam *cam)
{
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
		if (cub->map[cam->mapY][cam->mapX]
				&& cub->map[cam->mapY][cam->mapX] == '1')
			cam->wall_hit = 1;
	}
	if (cam->hit_type == 0)
		cam->dist = cam->sideDistX - cam->deltaDistX;
	else
		cam->dist = cam->sideDistY - cam->deltaDistY;
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
		cam->deltaDistX = fabs(1 / cam->rayDir.x);
		cam->deltaDistY = fabs(1 / cam->rayDir.y);
		cam->mapX = (player.pos.x / TILE_SIZE);
		cam->mapY = (player.pos.y / TILE_SIZE);
		(ray_calc(player, cam), throw_ray(cub, cam));
		paint_ray(cub, &x);
		x++;
	}
}
