/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:26:22 by made-jes          #+#    #+#             */
/*   Updated: 2025/03/29 23:24:42 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_enemy_images(t_data *data)
{
	int	img_width;
	int	img_height;

	data->image.enemy_right = mlx_xpm_file_to_image(data->mlx,
			ENEMY_RIGHT, &img_width, &img_height);
	data->image.enemy_left = mlx_xpm_file_to_image(data->mlx,
			ENEMY_LEFT, &img_width, &img_height);
	if (!data->image.enemy_right || !data->image.enemy_left)
		return (-1);
	return (0);
}

int	load_environment_images(t_data *data)
{
	int	img_width;
	int	img_height;

	data->image.wall = mlx_xpm_file_to_image(data->mlx,
			WALL, &img_width, &img_height);
	data->image.exit = mlx_xpm_file_to_image(data->mlx,
			EXIT, &img_width, &img_height);
	data->image.collectible = mlx_xpm_file_to_image(data->mlx,
			COLLECTIBLE, &img_width, &img_height);
	data->image.overlay = mlx_xpm_file_to_image(data->mlx,
			OVERLAY, &img_width, &img_height);
	if (!data->image.collectible || !data->image.exit || !data->image.wall
		|| !data->image.overlay)
		return (-1);
	return (0);
}

int	is_valid_move(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return (0);
	if (data->map.layout[y][x] == '1')
		return (0);
	return (1);
}

void	redraw_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	render_map(data);
	draw_player(data);
}
