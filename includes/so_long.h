/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:43:55 by made-jes          #+#    #+#             */
/*   Updated: 2025/03/26 22:54:17 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/minilibx-linux/mlx_int.h"

//To play with WASD keys
# define W 119
# define A 97
# define S 115
# define D 100

//To play with arrows keys
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363

//To close the window with the ESC
# define ESC 65307

//to define the images paths
# define PLAYER_RIGHT "./assets/player_right.xpm"
# define PLAYER_RIGHT1 "./assets/player_right_1.xpm"
# define PLAYER_LEFT "./assets/player_left.xpm"
# define PLAYER_LEFT1 "./assets/player_left_1.xpm"
# define WALL "./assets/wall.xpm"
# define EXIT "./assets/exit.xpm"
# define COLLECTIBLE "./assets/collectible.xpm"
# define OVERLAY "./assets/overlay.xpm"
# define ENEMY_RIGHT "./assets/enemy_right.xpm"
# define ENEMY_LEFT "./assets/enemy_left.xpm"

# include <stdio.h>
# include <unistd.h>

typedef struct s_player
{
	int			x;
	int			y;
	int			direction;
	int			frame;
}				t_player;

typedef struct s_enemy
{
	int				x;
	int				y;
	int				direction;
}				t_enemy;

typedef struct s_map
{
	char		**layout;
	int			width;
	int			height;
	int			cols;
	int			rows;
}				t_map;

typedef struct s_flags
{
	int			wall;
	int			player;
	int			collectible;
	int			exit;
	int			errors;
	int			enemy;
}				t_flags;

typedef struct s_image
{
	void		*collectible;
	void		*wall;
	void		*exit;
	void		*player_right[2];
	void		*player_left[2];
	void		*overlay;
	void		*enemy_right;
	void		*enemy_left;
}				t_image;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			moves;
	int			screen_width;
	int			screen_height;
	t_image		image;
	t_flags		flags;
	t_player	player;
	t_map		map;
	t_enemy		enemy;
}				t_data;

//Map
char	*read_map_layout(int fd);
void	get_map(t_map *map, char *av);
char	**copy_map(char **original);
void	render_map(t_data *data);
void	render_tile(t_data *data, int x, int y);
void	render_overlay(t_data *data);

//Utils
void	flood_fill(char **map, int x, int y, int rows);
void	init_flags(t_flags *flags, t_data *data);
void	find_player(t_data *data);
void	find_enemy(t_data *data);
int		init_data(t_data *data, int ac, char **av);
int		init_mlx_resources(t_data *data);
void	handle_interations(t_data *data, int new_x, int new_y);
void	display_moves(t_data *data);
int		is_move_key(int keycode);

//Checker for the map
int		check_map_name(char *av);
int		check_map_format(t_data *data);
void	check_objects(t_flags *flags, t_data *data);
int		check_row(char *row, char wall);
int		check_limits(t_data *data);
int		check_map(t_data *data, t_flags *flags);
int		validate_flood_fill(t_data *data);
int		check_for_collectibles_or_exit(char **map_copy, int rows, int cols);

//Free_exit
int		close_window(t_data *data);
void	free_map(char **map, int rows);
int		free_on_error(t_data *data, char *message);

//Gameplay
int		load_images(t_data *data);
int		load_environment_images(t_data *data);
int		load_enemy_images(t_data *data);
int		load_player_images(t_data *data);
int		is_valid_move(t_data *data, int x, int y);
int		move_player(int keycode, t_data *data);
void	set_directions(int keycode, t_data *data, int *x, int *y);
void	redraw_game(t_data *data);
void	gameplay(t_data *data);
void	draw_player(t_data *data);
void	move_enemy(t_data *data);
int		game_loop(t_data *data);

#endif