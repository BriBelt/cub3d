/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:41:26 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/23 17:49:41 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_down(int keycode, t_cub *cub, double *x, double *y)
{
	int			speed;
	t_player	*player;

	player = &cub->player;
	speed = 1;
	if (keycode == S)
	{
		*x -= player->dir.x * speed;
		*y -= player->dir.y * speed;
		if (!collision(*x, *y, cub->map))
		{
			player->pos.x = *x;
			player->pos.y = *y;
		}
	}
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
	move_down(keycode, cub, &new_x, &new_y);
	draw_screen(cub);
}

void	move_left(int keycode, t_cub *cub, double *x, double *y)
{
	t_player	*player;
	int			speed;
	t_cam		cam;

	player = &cub->player;
	speed = 1;
	cam = cub->cam;
	if (keycode == A)
	{
		*x -= cam.plane.x * speed;
		*y -= cam.plane.y * speed;
		if (!collision(*x, *y, cub->map))
		{
			player->pos.x = *x;
			player->pos.y = *y;
		}
	}
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
	move_left(keycode, cub, &new_x, &new_y);
	draw_screen(cub);
}
