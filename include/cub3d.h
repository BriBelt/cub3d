/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:36:29 by bbeltran          #+#    #+#             */
/*   Updated: 2023/10/30 15:34:58 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*		ERROR MESSAGES		*/
# define USAGE "Usage: ./cub3d filename.cub\n"
# define ERRFORMAT "Error: %s: File should be in the \".cub\" format\n"
# define ERROPEN "Error: %s: No access to the file\n"
# define ERRMEM "Error: %s: Memory error\n"
# define ERRCOLOR "Error: Non-valid RGB value\n"
# define ERRTEXT "Error: Non-valid textures\n"
# define ERRMAP "Error: Non-valid map\n"

/*			KEYBOARD		*/
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

/*		WINDOW			*/
# define WIDTH 1024
# define HEIGHT 512
# define TILE_SIZE 16

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

enum	e_tx_type
{
	NON,
	NO,
	SO,
	WE,
	EA,
};

enum	e_map_char
{
	NOT_VALID,
	OPEN,
	WALL,
	PLAYER,
	SPACE,
};

/* Structure for the image creation process, this will be passed to the
 * mlx_new_image() to create each image. */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		endian;
	int		len;
	int		bpp;
}				t_img;

typedef struct s_player
{
	float	x;
	float	y;
//	float	fov;
	float	rotation;
	int		move;
	int		turn;
	int		m_speed;
	int		t_speed;

}				t_player;

/* Structure for all the needed variables for the mlx library. */
typedef struct s_mlx
{
	void	*window;
	void	*connect;
	void	*background;
	t_img	img_background;
//	Should include void * for textures
}				t_mlx;

/* Structure for the textures. */
typedef struct s_tex
{
	char			*path;
	int				type;
	struct s_tex	*next;
}				t_tex;

/* Structure with char **map's info*/
typedef struct s_map_data
{
	int	x_len;
	int	y_len;
}			t_map_data;

/* Structure for minimap*/
typedef struct s_minimap
{
	int	x_size;
	int	y_size;
}				t_minimap;

/* Main Structure for game. */
typedef struct s_cub
{
	char		**map;
	int			ceiling[3];
	int			floor[3];
	t_tex		**textures;
	t_mlx		mlx;
	t_player	player;
	t_minimap	minimap;
	t_map_data	map_data;
}				t_cub;

/*		cub3d		*/
int		check_extension(char *filename);
/*		t_tex__utils	*/
void	t_tex_free(t_tex **lst);
void	insert_node(t_tex **lst, t_tex *node);
t_tex	*create_node(char *texture_path, int type);
int		t_tex_size(t_tex *lst);
/*		tc_utils		*/
int		check_rgb_code(int *rgb_code);
int		only_numbers(char *str);
int		check_extension(char *filename);
/*		fetch_header_data		*/
t_cub	*fetch_header_data(int file_fd);
/*		map_parsing				*/
char	**get_map(char *filename);
int		valid_char(char c);
/*		checkers				*/
char	*get_spaced_line(char *str, int len);
int		check_cub_struct(t_cub *cub);
/*		array_utils				*/
int		get_2d_array_size(char **array);
char	**copy_spaced_map(char **map);
void	free_2d_array(char **array);
/*		keyboard				*/
int		key_press(int keycode, t_cub *cub);
/*		player					*/
void	render_player(t_mlx mlx, t_player player);
t_player	get_player_position(char **map);
/*		images					*/
t_img	create_image(t_mlx mlx);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
/*		mini_map				*/
void	paint_mini_map(t_cub *cub);
void	render_background(t_cub *cub);
void	render_minimap(t_cub *cub);

#endif
