/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:28:51 by jaimmart          #+#    #+#             */
/*   Updated: 2023/11/26 18:09:13 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks(void)
{
	system("leaks cub3D");
}

void	init_game(t_cub *cub)
{
	cub->mlx.connect = mlx_init();
	cub->mlx.window = mlx_new_window(cub->mlx.connect, WIDTH, HEIGHT, "cub3d");
	mlx_hook(cub->mlx.window, 17, 0, (void *)exit, 0);
	mlx_hook(cub->mlx.window, 2, 1L << 0, keypress, cub);
	init_textures(cub);
	init_player_plane(&cub->player, &cub->cam, cub->map);
	draw_screen(cub);
	mlx_loop(cub->mlx.connect);
}

void	free_cub(t_cub *cub)
{
	free_2d_array(cub->map);
	destroy_textures(cub->textures, cub);
	t_tex_free(cub->textures);
	free(cub);
}

int	parsing(char *filename, t_cub *cub)
{
	int		fd;

	if (!check_extension(filename, ".cub"))
		return (printf(ERRFORMAT, filename), free(cub), 0);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (printf(ERROPEN, filename), 0);
	if (!fetch_header_data(fd, cub))
		return (free(cub), 0);
	if (!*cub->textures)
	{
		printf("no list\n");
		return (printf(ERRTEXT), free(cub->textures), free(cub), 0);
	}
	if (!check_textures(cub->textures))
	{
		printf("checkerr\n");
		return (printf(ERRTEXT), free(cub), 0);
	}
	if (!get_map(filename, cub))
		return (printf(ERRMAP), t_tex_free(cub->textures), free(cub), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	atexit(leaks);
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (printf(ERRMEM, "fetch_header_data"), 0);
	if (argc != 2)
		return (printf(USAGE), 1);
	if (!parsing(argv[1], cub))
		return (1);
	if (!check_cub_struct(cub))
		return (1);
	init_game(cub);
	free_cub(cub);
	return (0);
}
