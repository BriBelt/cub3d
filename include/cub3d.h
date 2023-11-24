/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:36:29 by bbeltran          #+#    #+#             */
/*   Updated: 2023/11/24 14:14:36 by bbeltran         ###   ########.fr       */
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
# define ERRCOL2 "Error: Non-valid color identifier\n"

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
	int		*addr;
	int		endian;
	int		len;
	int		bpp;
	int		h;
	int		w;
}				t_img;

/* Structure for all the needed variables for the mlx library. */
typedef struct s_mlx
{
	void	*window;
	void	*connect;
	t_img	frame;
}				t_mlx;

/* Structure for the textures. */
typedef struct s_tex
{
	char			*path;
	int				type;
	t_img			img;
	int				size;
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

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
}				t_player;

typedef struct	s_cam
{
	t_vector	plane;
	t_vector	rayDir;
	int			stepX;
	int			stepY;
	int			mapX;
	int			mapY;
	int			wall_hit;
	int			hit_type;
	double		fov;
	double		cam_x;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		dist;
	double		wallX;
	int			texX;
	int			texY;
	double		texStep;
	double		texPos;
}				t_cam;

/* Main Structure for game. */
typedef struct s_cub
{
	char			**map;
	unsigned int	ceiling[3];
	unsigned int	floor[3];
	unsigned long	cceiling;
	unsigned long	cfloor;
	int				start;
	t_cam			cam;
	t_tex			**textures;
	t_mlx			mlx;
	t_minimap		minimap;
	t_map_data		map_data;
	t_player		player;
}					t_cub;

/*		cub3d		*/
/*		t_tex__utils	*/
void			t_tex_free(t_tex **lst);
int				valid_txt(t_tex *node);
void			insert_node(t_tex **lst, t_tex *node);
t_tex			*create_node(char *texture_path, int type);
int				t_tex_size(t_tex *lst);
/*		tc_utils		*/
int				check_rgb_code(unsigned int *rgb_code);
int				only_numbers(char *str);
int				check_extension(char *filename, char *ext);
/*		fetch_header_data		*/
t_cub			*fetch_header_data(int file_fd);
/*		map_parsing				*/
char			**get_map(char *filename);
int				valid_char(char c);
/*		checkers				*/
char			*get_spaced_line(char *str, int len);
int				check_cub_struct(t_cub *cub);
/*		array_utils				*/
int				get_2d_array_size(char **array);
size_t			get_longest_line(char **map);
char			**copy_spaced_map(char **map);
void			free_2d_array(char **array);
/*		images					*/
unsigned long	convert_rgb(unsigned int r, unsigned int g, unsigned int b);
void			create_image(t_mlx mlx, t_img *img);
/*		draw					*/
void			load_background(t_cub *cub, int height, int end, int x);
t_img			select_texture(t_cub *cub, t_cam cam);
void			paint_ray(t_cub *cub, int *x);
void			draw_screen(t_cub *cub);
/*		player					*/
void			init_player_plane(t_player *player, t_cam *cam, char **map);
/*		keyboard				*/
void			close_game(t_cub *cub);
int				keypress(int keycode, t_cub *cub);
/*		moves					*/
void			move_up_down(int keycode, t_cub *cub);
void			move_left_right(int keycode, t_cub *cub);
/*		ray						*/
int				collision(double x, double y, char **map);
void			raycaster(t_cub *cub);
/*		textures				*/
void			init_textures(t_cub *cub);
void			destroy_textures(t_tex **textures, t_cub *cub);
unsigned int	get_tex_color(t_cub *cub, double start, double draw_height);
void			get_tex_x(t_cub *cub, t_tex *tex);

#endif
