/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:45:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/27 16:36:06 by bbeltran         ###   ########.fr       */
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
	double				step;
	t_cam				*cam;
	t_img				img;

	cam = &cub->cam;
	img = select_texture(cub, *cam);
	step = 1.0 * img.h / draw_height;
	cam->tex_pos = (start - HEIGHT / 2 + draw_height / 2) * step;
	cam->tex_y = (int)cam->tex_pos & (img.h - 1);
	cam->tex_pos += step;
	color = img.addr[img.h * cam->tex_y + cam->tex_x];
	if (cam->hit_type == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

void	get_tex_x(t_cub *cub, t_tex *tex)
{
	t_cam		*cam;
	t_player	player;
	double		p_posx;
	double		p_posy;

	(void)tex;
	cam = &cub->cam;
	player = cub->player;
	p_posy = player.pos.y / TILE_SIZE;
	p_posx = player.pos.x / TILE_SIZE;
	if (cam->hit_type == 0)
		cam->wall_x = p_posy + cam->dist * cam->raydir.y;
	else
		cam->wall_x = p_posx + cam->dist * cam->raydir.x;
	cam->wall_x -= floor(cam->wall_x);
	cam->tex_x = (int)(cam->wall_x * (double)TILE_SIZE);
	if (cam->hit_type == 1 && cam->raydir.y > 0)
		cam->tex_x = TILE_SIZE - cam->tex_x - 1;
	if (cam->hit_type == 0 && cam->raydir.x < 0)
		cam->tex_x = TILE_SIZE - cam->tex_x - 1;
}
