/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:25:00 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/23 17:36:34 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	get_player_view(double *x, double *y, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (valid_char(map[i][j]) == PLAYER)
			{
				*x = j * TILE_SIZE;
				*y = i * TILE_SIZE;
				return (map[i][j]);
			}
		}
	}
	return (0);
}

void	rest_of_init(t_player *player, t_cam *cam, char view)
{
	if (view == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		cam->plane.x = 0;
		cam->plane.y = -0.66;
	}
	else if (view == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		cam->plane.x = 0;
		cam->plane.y = 0.66;
	}
}

void	init_player_plane(t_player *player, t_cam *cam, char **map)
{
	char	view;

	view = get_player_view(&player->pos.x, &player->pos.y, map);
	player->pos.x += TILE_SIZE / 2;
	player->pos.y += TILE_SIZE / 2;
	if (view == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		cam->plane.x = -0.66;
		cam->plane.y = 0;
	}
	else if (view == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		cam->plane.x = 0.66;
		cam->plane.y = 0;
	}
	rest_of_init(player, cam, view);
}
