/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:43:18 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/26 16:30:51 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	collision(double x, double y, char **map)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map[map_y][map_x] && map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	ray_calc(t_player player, t_cam *cam)
{
	if (cam->raydir.x < 0)
	{
		cam->step_x = -1;
		cam->sidedist_x = ((player.pos.x / TILE_SIZE) - cam->map_x)
			* cam->deltadist_x;
	}
	else
	{
		cam->step_x = 1;
		cam->sidedist_x = (cam->map_x + 1 - (player.pos.x / TILE_SIZE))
			* cam->deltadist_x;
	}
	if (cam->raydir.y < 0)
	{
		cam->step_y = -1;
		cam->sidedist_y = ((player.pos.y / TILE_SIZE) - cam->map_y)
			* cam->deltadist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->sidedist_y = (cam->map_y + 1 - (player.pos.y / TILE_SIZE))
			* cam->deltadist_y;
	}
}

void	throw_ray(t_cub *cub, t_cam *cam)
{
	while (!cam->wall_hit)
	{
		if (cam->sidedist_x < cam->sidedist_y)
		{
			cam->hit_type = 0;
			cam->sidedist_x += cam->deltadist_x;
			cam->map_x += cam->step_x;
		}
		else
		{
			cam->hit_type = 1;
			cam->sidedist_y += cam->deltadist_y;
			cam->map_y += cam->step_y;
		}
		if (cub->map[cam->map_y][cam->map_x]
				&& cub->map[cam->map_y][cam->map_x] == '1')
			cam->wall_hit = 1;
	}
	if (cam->hit_type == 0)
		cam->dist = cam->sidedist_x - cam->deltadist_x;
	else
		cam->dist = cam->sidedist_y - cam->deltadist_y;
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
		cam->step_x = 0;
		cam->step_y = 0;
		cam->wall_hit = 0;
		cam->cam_x = ((2 * x) / (double)WIDTH) - 1;
		cam->raydir.x = player.dir.x + cam->plane.x * cam->cam_x;
		cam->raydir.y = player.dir.y + cam->plane.y * cam->cam_x;
		cam->deltadist_x = fabs(1 / cam->raydir.x);
		cam->deltadist_y = fabs(1 / cam->raydir.y);
		cam->map_x = (player.pos.x / TILE_SIZE);
		cam->map_y = (player.pos.y / TILE_SIZE);
		(ray_calc(player, cam), throw_ray(cub, cam));
		paint_ray(cub, &x);
		x++;
	}
}
