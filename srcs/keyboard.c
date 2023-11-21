/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:35:51 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/21 16:11:30 by bbeltran         ###   ########.fr       */
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

void	move_up_down(int keycode, t_cub *cub)
{
	int			speed;
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &cub->player;
	speed = 1;
	new_x = player->pos.x;
	new_y = player->pos.y;
	if (keycode == W)
	{
		new_x += player->dir.x * speed;
		new_y += player->dir.y * speed;
		if (!collision(new_x, new_y, cub->map))
		{
			player->pos.x = new_x;
			player->pos.y = new_y;
		}
	}
	if (keycode == S)
	{
		new_x -= player->dir.x * speed;
		new_y -= player->dir.y * speed;
		if (!collision(new_x, new_y, cub->map))
		{
			player->pos.x = new_x;
			player->pos.y = new_y;
		}
	}
	draw_screen(cub);
}

void	move_left_right(int keycode, t_cub *cub)
{
	int			speed;
	t_player	*player;
	t_cam		cam;
	double		new_x;
	double		new_y;
	
	player = &cub->player;
	speed = 1;
	cam = cub->cam;
	new_x = player->pos.x;
	new_y = player->pos.y;
	if (keycode == D)
	{
		new_x += cam.plane.x * speed;
		new_y += cam.plane.y * speed;
		if (!collision(new_x, new_y, cub->map))
		{
			player->pos.x = new_x;
			player->pos.y = new_y;
		}
	}
	if (keycode == A)
	{
		new_x -= cam.plane.x * speed;
		new_y -= cam.plane.y * speed;
		if (!collision(new_x, new_y, cub->map))
		{
			player->pos.x = new_x;
			player->pos.y = new_y;
		}
	}
	draw_screen(cub);
}

void	rotate_left_right(int keycode, t_cub *cub)
{
	double		speed;
	t_player	*player;
	t_cam		*cam;

	player = &cub->player;
	cam = &cub->cam;
	speed = (2 * M_PI / 180);
	if (keycode == RIGHT)
	{
		player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
		player->dir.y = player->dir.x * sin(speed) + player->dir.y * cos(speed);
		cam->plane.x = cam->plane.x * cos(speed) - cam->plane.y * sin(speed);
		cam->plane.y = cam->plane.x * sin(speed) + cam->plane.y * cos(speed);
	}
	if (keycode == LEFT)
	{
		player->dir.x = player->dir.x * cos(-speed) - player->dir.y * sin(-speed);
		player->dir.y = player->dir.x * sin(-speed) + player->dir.y * cos(-speed);
		cam->plane.x = cam->plane.x * cos(-speed) - cam->plane.y * sin(-speed);
		cam->plane.y = cam->plane.x * sin(-speed) + cam->plane.y * cos(-speed);
	}
	draw_screen(cub);
}

void	close_game(t_cub *cub)
{
	mlx_destroy_window(cub->mlx.connect, cub->mlx.window);
	exit(0);
}

int	keypress(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		close_game(cub);
	if (keycode == W)
		move_up_down(keycode, cub);
	if (keycode == S)
		move_up_down(keycode, cub);
	if (keycode == A)
		move_left_right(keycode, cub);
	if (keycode == D)
		move_left_right(keycode, cub);
	if (keycode == LEFT)
		rotate_left_right(keycode, cub);
	if (keycode == RIGHT)
		rotate_left_right(keycode, cub);
	return (0);
}
