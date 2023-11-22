/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:24:46 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/22 13:06:31 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_rgb_code(unsigned int *rgb_code)
{
	if (rgb_code[0] < 0 || rgb_code[0] > 255)
		return (0);
	if (rgb_code[1] < 0 || rgb_code[1] > 255)
		return (0);
	if (rgb_code[2] < 0 || rgb_code[2] > 255)
		return (0);
	return (1);
}

int	only_numbers(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '\n' && !ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	check_extension(char *filename)
{
	int		i;
	int		j;
	char	*ext;

	ext = ".cub";
	i = ft_strlen(filename);
	j = ft_strlen(ext);
	while (j >= 0)
	{
		if (filename[i--] != ext[j--])
			return (0);
	}
	return (1);
}
