/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:28:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/08 16:39:36 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_player_direction(t_player *player)
{
	player->down = 0;
	player->left = 0;
	if (player->rotation < PI)
		player->down = 1;
	if (player->rotation < 3 * (PI / 2) && player->rotation > PI / 2)
		player->left = 1;
}

/*llamar en move_player()*/
double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int	collision(double x, double y, char **map)
{
	int	y_tile;
	int	x_tile;

	x_tile = floor(x / TILE_SIZE);
	y_tile = floor(y / TILE_SIZE);
	if (x_tile > (int)ft_strlen(map[y_tile]))
		return (1);
	if (!map[y_tile][x_tile] || map[y_tile][x_tile] == '1')
		return (1);
	return (0);
}

t_player	get_player_position(char **map)
{
	t_player	player;
	int			i;
	int			j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'E'
					|| map[i][j] == 'S')
			{
				player.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
				player.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			}
		}
	}
	return (player);
}

void	init_player_stats(t_player *player)
{
	player->rotation = 4.5;
	player->dest_x = 0,
	player->dest_y = 0,
	player->move = 0;
	player->turn = 0;
	player->m_speed = 3;
	player->t_speed = 3 * (PI / 180);
}

void	render_ray(t_mlx mlx, t_player player, t_ray ray, double angle)
{
	unsigned int color = 0x0000FF00;
	double		x;
	double		y;
	int			i;

	i = 1;
	x = player.x;
	y = player.y;
	if (ray.down && !ray.left)
	{
		while (x <= ray.wallHit_x && y <= ray.wallHit_y)
		{
			x = player.x + (cos(angle) * i);
			y = player.y + (sin(angle) * i);
			mlx_pixel_put(mlx.connect, mlx.window, floor(x), floor(y), color);
			i++;
		}
	}
	if (ray.down && ray.left)
	{
		while (x >= ray.wallHit_x && y <= ray.wallHit_y)
		{
			x = player.x + (cos(angle) * i);
			y = player.y + (sin(angle) * i);
			mlx_pixel_put(mlx.connect, mlx.window, floor(x), floor(y), color);
			i++;
		}
	}
	if (!ray.down && !ray.left)
	{
		while (x <= ray.wallHit_x && y >= ray.wallHit_y)
		{
			x = player.x + (cos(angle) * i);
			y = player.y + (sin(angle) * i);
			mlx_pixel_put(mlx.connect, mlx.window, floor(x), floor(y), color);
			i++;
		}
	}
	if (!ray.down && ray.left)
	{
		while (x >= ray.wallHit_x && y >= ray.wallHit_y)
		{
			x = player.x + (cos(angle) * i);
			y = player.y + (sin(angle) * i);
			mlx_pixel_put(mlx.connect, mlx.window, floor(x), floor(y), color);
			i++;
		}
	}
}

void	render_direction(t_mlx mlx, t_player player)
{
	int		i;
	double	x;	
	double	y;	
	unsigned int color = 0x00FF0000;

	i = 0;
	while (++i < 20)
	{
		x = player.x + (cos(player.rotation) * i);
		y = player.y + (sin(player.rotation) * i);
		mlx_pixel_put(mlx.connect, mlx.window, floor(x), floor(y), color);
	}
}

void	render_player(t_mlx mlx, t_player player)
{
	unsigned int color = 0x00FF0000;

	mlx_pixel_put(mlx.connect, mlx.window, player.x, player.y, color);
	mlx_pixel_put(mlx.connect, mlx.window, player.x, player.y + 1, color);
	mlx_pixel_put(mlx.connect, mlx.window, player.x + 1, player.y, color);
	mlx_pixel_put(mlx.connect, mlx.window, player.x + 1, player.y + 1, color);
//	render_direction(mlx, player);
//
}
