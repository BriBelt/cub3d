/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:35:37 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/26 17:06:55 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	valid_char(char c)
{
	if (c == '1')
		return (WALL);
	if (c == '0')
		return (OPEN);
	if (c == ' ')
		return (SPACE);
	if (c == 'N')
		return (PLAYER);
	if (c == 'S')
		return (PLAYER);
	if (c == 'W')
		return (PLAYER);
	if (c == 'E')
		return (PLAYER);
	return (NOT_VALID);
}

int	map_valid_chars(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		if (!valid_char(line[i]))
			return (0);
	}
	return (1);
}

int	get_array_size(char *filename)
{
	int		size;
	int		file_fd;
	char	*line;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (printf(ERROPEN, filename), 0);
	size = 0;
	line = get_next_line(file_fd);
	while (line && (!ft_strcmp(line, "\n") || !map_valid_chars(line)))
	{
		free(line);
		line = get_next_line(file_fd);
	}
	while (line)
	{
		if (!map_valid_chars(line))
			return (free(line), 0);
		size++;
		free(line);
		line = get_next_line(file_fd);
	}
	close(file_fd);
	return (size);
}

int	get_map2(t_cub *cub, char *line, int file_fd, int i)
{
	while (line && (!ft_strcmp(line, "\n") || !map_valid_chars(line)))
	{
		free(line);
		line = get_next_line(file_fd);
	}
	while (line)
	{
		if (!ft_strcmp(line, "\n"))
			break ;
		if (!map_valid_chars(line))
			return (free_2d_array(cub->map), free(line), close(file_fd), 0);
		cub->map[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(file_fd);
	}
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			return (free_2d_array(cub->map), free(line), close(file_fd), 0);
		free(line);
		line = get_next_line(file_fd);
	}
	return (1);
}

int	get_map(char *filename, t_cub *cub)
{
	int		arr_size;
	int		file_fd;
	int		i;
	char	*line;

	i = 0;
	arr_size = get_array_size(filename);
	if (!arr_size)
		return (0);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (printf(ERROPEN, filename), 0);
	cub->map = ft_calloc(arr_size + 1, sizeof(char *));
	if (!cub->map)
		return (printf(ERRMEM, "get_map"), close(file_fd), 0);
	line = get_next_line(file_fd);
	if (!get_map2(cub, line, file_fd, i))
		return (0);
	return (close(file_fd), 1);
}
