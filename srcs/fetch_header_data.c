/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_header_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:11:24 by bbeltran          #+#    #+#             */
/*   Updated: 2023/10/24 17:29:42 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	manage_textures(t_cub *cub, char **array)
{
	int	type;

	type = NON;
	if (!ft_strcmp(array[0], "NO"))
		type = NO;
	if (!ft_strcmp(array[0], "SO"))
		type = SO;
	if (!ft_strcmp(array[0], "WE"))
		type = WE;
	if (!ft_strcmp(array[0], "EA"))
		type = EA;
	insert_node(cub->textures, create_node(array[1], type));
}

int	manage_colors(t_cub *cub, char **array, char type)
{
	char	**rgb;
	int		rgb_code[3];
	int		i;

	rgb = ft_split(array[1], ',');
	free_2d_array(array);
	if (!rgb)
		return (0);
	i = -1;
	while (rgb[++i])
	{
		if (!only_numbers(rgb[i]))
			return (printf(ERRCOLOR, rgb[i]), free_2d_array(rgb), 0);
	}
	rgb_code[0] = ft_atoi(rgb[0]);
	rgb_code[1] = ft_atoi(rgb[1]);
	rgb_code[2] = ft_atoi(rgb[2]);
	if (!check_rgb_code(rgb_code))
		return (printf(ERRCOLOR, "rgb_code"), free_2d_array(rgb), 0);
	if (type == 'F')
	{
		cub->floor[0] = rgb_code[0];
		cub->floor[1] = rgb_code[1];
		cub->floor[2] = rgb_code[2];
	}
	else if (type == 'C')
	{
		cub->ceiling[0] = rgb_code[0];
		cub->ceiling[1] = rgb_code[1];
		cub->ceiling[2] = rgb_code[2];
	}
	return (free_2d_array(rgb), 1);
}

int	clean_line(t_cub *cub, char *line)
{
	char	**array;

	if (!line)
		return (0);
	array = ft_split(line, ' ');
	if (!ft_strcmp(array[0], "F"))
		return (manage_colors(cub, array, 'F'));
	if (!ft_strcmp(array[0], "C"))
		return (manage_colors(cub, array, 'C'));
	if (!ft_strcmp(array[0], "NO") || !ft_strcmp(array[0], "SO")
		|| !ft_strcmp(array[0], "WE") || !ft_strcmp(array[0], "EA"))
		manage_textures(cub, array);
	free_2d_array(array);
	return (1);
}

t_cub	*fetch_header_data(int file_fd)
{
	char	*line;
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (printf(ERRMEM, "fetch_header_data"), NULL);
	cub->textures = malloc(sizeof(t_tex *));
	if (!cub->textures)
		return (printf(ERRMEM, "fetch_header_data"), NULL);
	*cub->textures = NULL;
	line = get_next_line(file_fd);
	while (line)
	{
		while (line && !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(file_fd);
		}
		if (!line)
			break ;
		if (!clean_line(cub, line))
			return (free(line), NULL);
		// put error
		free(line);
		line = get_next_line(file_fd);
	}
	close(file_fd);
	return (cub);
}
