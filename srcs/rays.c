/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:26:51 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/14 17:21:13 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_ray_direction(double angle, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	if (angle < PI)
		ray->down = 1;
	if (angle < 3 * (PI / 2) && angle > PI / 2)
		ray->left = 1;
}

int	check_limits(t_cub cub, double next_x, double next_y)
{
	if (next_x >= 0 && next_y >= 0)
	{
		if (next_x < cub.minimap.x_size && next_y < cub.minimap.y_size)
			return (1);
	}
	return (0);
}

/*void	normalize_distance(t_cub *cub)
{
	double	new_angle;
	int		ray_n;

	ray_n  = 0;
	while (ray_n < WIDTH)
	{
		if (ray_n < WIDTH / 2)
			new_angle = ((PI / 180) * 45) + (ray_n * ((PI / 180) * 90) / WIDTH);
		else if (ray_n >= WIDTH / 2)
			new_angle = ((PI / 180) * 45) + ((511 - ray_n) * ((PI / 180) * 90) / WIDTH);
//		new_angle = ((PI / 180) * 90) - ((PI / 180) * 30) - (ray_n * ((PI / 180) * 60) / WIDTH);
//		if (ray_n < 10 || ray_n > 501)
		if (ray_n < 10 || ray_n > 501 || (ray_n > 250 && ray_n < 260))
			printf("distancia[%d] = %f\n",ray_n, cub->ray[ray_n].distance);
		if (new_angle < 0)
			new_angle *= -1;
		cub->ray[ray_n].distance *= sin(new_angle);
		if (ray_n < 10 || ray_n > 501 || (ray_n > 250 && ray_n < 260))
			printf("angulo[%d] = %f -- dist: %f\n",ray_n,  new_angle, cub->ray[ray_n].distance);
		ray_n++;
	}
}*/

void	normalize_distance(t_cub *cub)
{
	double	new_angle;
	int		ray_n;

	ray_n  = 0;
	while (ray_n < WIDTH)
	{
		new_angle = fabs(cub->player.rotation - cub->ray[ray_n].angle);
		cub->ray[ray_n].distance *= cos(new_angle);
		ray_n++;
	}
}
double	ray_distance(t_ray *ray)
{
	double	distance;
	double	x;
	double	y;

	x = sqrt((ray->wallHit_x - ray->x) * (ray->wallHit_x - ray->x));
	y = sqrt((ray->wallHit_y - ray->y) * (ray->wallHit_y - ray->y));
	distance = x + y;
	return (distance);
}

void	get_ray_y(t_ray *ray, t_cub cub, double angle)
{
	double	adjacent;
	double	next_x_intercept;
	double	next_y_intercept;
	int		horizontalCol;

	horizontalCol = 0;
	ray->y_intercept = floor(ray->y/TILE_SIZE) * TILE_SIZE;
	if (ray->down)
		ray->y_intercept += TILE_SIZE;
	adjacent = (ray->y_intercept - ray->y) / tan(angle);
	ray->x_intercept = ray->x + adjacent;
	ray->y_step = TILE_SIZE;
	ray->x_step = ray->y_step / tan(angle);
	if (!ray->down)
		ray->y_step *= -1;
	if ((ray->left && ray->x_step > 0) || (!ray->left && ray->x_step < 0))
		ray->x_step *= -1;
	next_x_intercept = ray->x_intercept;
	next_y_intercept = ray->y_intercept;
	if (!ray->down)
		next_y_intercept--;
	while (!horizontalCol && check_limits(cub, next_x_intercept,
			next_y_intercept))
	{
		if (collision(next_x_intercept, next_y_intercept, cub.map))
		{
			horizontalCol++;
			ray->wallHit_x = next_x_intercept;
			ray->wallHit_y = next_y_intercept;
		}
		else
		{
			next_x_intercept += ray->x_step;
			next_y_intercept += ray->y_step;
		}
	}
	if (horizontalCol)
	{
		ray->distance = ray_distance(ray);
//		new_angle = ray_n * 
//		ray->distance = ray->distance * cos(???);
//		ray->distance *= cos(cub.player.rotation - angle);
	}
}

void	get_ray_x(t_ray *ray, t_cub cub, double angle)
{
	double	next_x_intercept;
	double	next_y_intercept;
	double	opposite;
	int		verticalCol;

	verticalCol = 0;
	ray->x_intercept = floor(ray->x/TILE_SIZE) * TILE_SIZE;
	if (!ray->left)
		ray->x_intercept += TILE_SIZE;
	opposite = (ray->x_intercept - ray->x) * tan(angle);
	ray->y_intercept = ray->y + opposite;
	ray->x_step = TILE_SIZE;
	if (ray->left)
		ray->x_step *= -1;
	ray->y_step = TILE_SIZE * tan(angle);
	if ((!ray->down && ray->y_step > 0) || (ray->down && ray->y_step < 0))
		ray->y_step *= -1;
	next_x_intercept = ray->x_intercept;
	next_y_intercept = ray->y_intercept;
	if (ray->left)
		next_x_intercept--;
	while (!verticalCol && check_limits(cub, next_x_intercept,
			next_y_intercept))
	{
		if (collision(next_x_intercept, next_y_intercept, cub.map))
		{
			verticalCol++;
			ray->wallHit_x = next_x_intercept;
			ray->wallHit_y = next_y_intercept;
		}
		else
		{
			next_x_intercept += ray->x_step;
			next_y_intercept += ray->y_step;
		}
	}
	if (verticalCol)
	{
		ray->distance = ray_distance(ray);
//		ray->distance *= cos(cub.player.rotation - angle);
	}
}

t_ray	raycaster(t_cub cub, double angle)
{
	t_ray	ray_x;
	t_ray	ray_y;

	ray_x.x = cub.player.x;
	ray_x.y = cub.player.y;
	ray_y.x = cub.player.x;
	ray_y.y = cub.player.y;
	ray_y.distance = 9999;
	ray_x.distance = 9999;
	check_ray_direction(angle, &ray_x);
	check_ray_direction(angle, &ray_y);
	get_ray_y(&ray_y, cub, angle);
	get_ray_x(&ray_x, cub, angle);
	if (ray_y.distance < ray_x.distance)
		return (ray_y.type = 2, ray_y);
	return (ray_x.type = 1, ray_x);
}

void	create_ray_vision(t_cub *cub)
{
	int		i;
	double	angle;

	i = -1;
	angle = cub->player.rotation - ((PI / 180) * 30);
//	angle = normalize_angle(angle);
	while (++i < WIDTH)
	{
		cub->ray[i].angle = angle;
		cub->ray[i] = raycaster(*cub, angle);
		render_ray(cub->mlx, cub->player, cub->ray[i], angle);
		angle += ((PI / 180) * 60) / WIDTH;
		angle = normalize_angle(angle);
		cub->ray[i].angle = angle;
	}
}
