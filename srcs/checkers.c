/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:03:31 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/26 18:06:00 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_player(char **map)
{
	int	i;
	int	j;
	int	player_found;

	i = -1;
	player_found = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (valid_char(map[i][j]) == PLAYER)
				player_found++;
		}
	}
	if (player_found != 1)
		return (0);
	return (1);
}

char	*get_spaced_line(char *str, int len)
{
	char	*spaced_line;
	int		i;
	int		j;

	spaced_line = ft_calloc(len + 3, sizeof(char));
	if (!spaced_line)
		return (printf(ERRMEM, "get_spaced_line"), NULL);
	i = -1;
	j = 0;
	if (!str)
		ft_memset(spaced_line, ' ', len + 2);
	else
	{
		i = 0;
		spaced_line[i] = ' ';
		while (++i < len + 2)
		{
			if (str[j])
				spaced_line[i] = str[j++];
			else
				spaced_line[i] = ' ';
		}
	}
	return (spaced_line);
}

int	check_map(char **map, char **s_map)
{
	int			arr_y_size;
	int			i;
	size_t		j;
	size_t		arr_x_size;

	i = 0;
	if (!check_player(map))
		return (0);
	s_map = copy_spaced_map(map);
	arr_y_size = get_2d_array_size(s_map);
	arr_x_size = ft_strlen(s_map[0]);
	while (s_map[++i] && i < arr_y_size)
	{
		j = 0;
		while (s_map[i][++j] && j < arr_x_size)
		{
			if (s_map[i][j] == '0')
			{
				if (s_map[i - 1][j] == ' ' || s_map[i + 1][j] == ' ' ||
					s_map[i][j - 1] == ' ' || s_map[i][j + 1] == ' ')
					return (free_2d_array(s_map), 0);
			}
		}
	}
	return (free_2d_array(s_map), 1);
}

/* This function will check if the t_tex **textures list is correct, meaning
 * if the list has only four nodes, and those four nodes are not duplicated.
 * If the list doesn´t pass these two checks, returns 0, else returns 1. */
int	check_textures(t_tex **textures)
{
	t_tex	*curr;
	t_tex	*c;
	int		i;
	int		j;

	(*textures)->size = t_tex_size(*textures);
	if ((*textures)->size != 4)
		return (t_tex_free(textures), 0);
	curr = *textures;
	c = *textures;
	i = 0;
	while (curr)
	{
		j = 0;
		while (c)
		{
			if ((i != j && c->type == curr->type) || !valid_txt(c))
				return (t_tex_free(textures), 0);
			c = c->next;
			j++;
		}
		curr = curr->next;
		i++;
	}
	return (1);
}

int	check_cub_struct(t_cub *cub)
{
	char	**s_map;

	s_map = NULL;
	if (!cub->map)
		return (printf(ERRMAP), 0);
	if (!check_map(cub->map, s_map))
		return (printf(ERRMAP), free_2d_array(cub->map), 0);
	return (1);
}
