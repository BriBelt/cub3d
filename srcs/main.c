/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:28:51 by jaimmart          #+#    #+#             */
/*   Updated: 2023/11/24 14:05:08 by bbeltran         ###   ########.fr       */
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

t_cub	*parsing(char *filename)
{
	int		fd;
	t_cub	*cub;

	if (!check_extension(filename, ".cub"))
		return (printf(ERRFORMAT, filename), NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf(ERROPEN, filename), NULL);
	cub = fetch_header_data(fd);
	if (!cub)
		return (NULL);
	if (!cub->textures || !*cub->textures)
		return (NULL);
	cub->map = get_map(filename);
	if (!cub->map)
		return (printf(ERRMAP), NULL);
	if (!check_cub_struct(cub))
		return (free(cub), NULL);
	return (cub);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	atexit(leaks);
	if (argc != 2)
		return (printf(USAGE), 1);
	cub = parsing(argv[1]);
	if (!cub)
		return (free(cub), 1);
	init_game(cub);
	free_cub(cub);
	return (0);
}
