/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:25:00 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/20 16:48:42 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_plane_vector(t_cam *cam)
{
	cam->plane.x = -0.66;
	cam->plane.y = 0;
}

void	init_player_pos(t_player *player)
{
	player->pos.x = 50;
	player->pos.y = 50;
	player->dir.x = 0;
	player->dir.y = 1;
}
