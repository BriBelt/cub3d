/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:35:51 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/24 14:04:21 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		player->dir.x = player->dir.x * cos(-speed)
			- player->dir.y * sin(-speed);
		player->dir.y = player->dir.x * sin(-speed)
			+ player->dir.y * cos(-speed);
		cam->plane.x = cam->plane.x * cos(-speed) - cam->plane.y * sin(-speed);
		cam->plane.y = cam->plane.x * sin(-speed) + cam->plane.y * cos(-speed);
	}
	draw_screen(cub);
}

void	close_game(t_cub *cub)
{
	if (cub->mlx.frame.img)
		mlx_destroy_image(cub->mlx.connect, cub->mlx.frame.img);
	mlx_clear_window(cub->mlx.connect, cub->mlx.window);
	destroy_textures(cub->textures, cub);
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
