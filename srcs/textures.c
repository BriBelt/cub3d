/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:45:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/23 17:11:15 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_textures(t_tex **textures, t_cub *cub)
{
	t_tex	*curr;

	curr = *textures;
	while (curr)
	{
		if (curr->img.img)
			mlx_destroy_image(cub->mlx.connect, curr->img.img);
		curr = curr->next;
	}
}

void	init_textures(t_cub *cub)
{
	t_mlx	mlx;
	t_tex	*tex;
	t_img	*img;

	mlx = cub->mlx;
	tex = *cub->textures;
	while (tex)
	{
		img = &tex->img;
		img->img = mlx_xpm_file_to_image(mlx.connect, tex->path,
				&img->w, &img->h);
		if (!img->img)
			(printf("Error: mlx_xpm_file_to_image\n"), exit(1));
		img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->len,
				&img->endian);
		tex = tex->next;
	}
}

unsigned int	get_tex_color(t_cub *cub, double start, double draw_height)
{
	unsigned int		color;
	double			step;
	t_cam			*cam;
	t_img			img;

	cam = &cub->cam;
	img = select_texture(cub, *cam);
	step = 1.0 * img.h / draw_height;
	cam->texPos = (start - HEIGHT / 2 + draw_height / 2) * step;
	cam->texY = (int)cam->texPos & (img.h - 1);
	cam->texPos += step;
	color = img.addr[img.h * cam->texY + cam->texX];
	if (cam->hit_type == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

void	get_texX(t_cub *cub, t_tex *tex)
{
	t_cam		*cam;
	t_player	player;
	double		p_posx;
	double		p_posy;

	cam = &cub->cam;
	player = cub->player;
	p_posy = player.pos.y / TILE_SIZE;
	p_posx = player.pos.x / TILE_SIZE;
	if (cam->hit_type == 0)
		cam->wallX = p_posy + cam->dist * cam->rayDir.y;
	else
		cam->wallX = p_posx + cam->dist * cam->rayDir.x;
	cam->wallX -= floor(cam->wallX);
	cam->texX = (int)(cam->wallX * (double)tex->img.w);
	if (cam->hit_type == 1 && cam->rayDir.y > 0)
		cam->texX = tex->img.w - cam->texX - 1;
	if (cam->hit_type == 0 && cam->rayDir.x < 0)
		cam->texX = tex->img.w - cam->texX - 1;
}
