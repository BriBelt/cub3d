/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:29:56 by jaimmart          #+#    #+#             */
/*   Updated: 2023/11/23 17:57:59 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long	convert_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	create_image(t_mlx mlx, t_img *img)
{
	img->img = mlx_new_image(mlx.connect, WIDTH, HEIGHT);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->len, &img->endian);
}
