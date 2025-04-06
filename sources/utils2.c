/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:39:17 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/05 12:24:19 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_player(t_data *data)
{
	void	*img;

	if (data->player.direction == 0)
		img = data->image.player_left[data->player.frame];
	else
		img = data->image.player_right[data->player.frame];
	mlx_put_image_to_window(data->mlx, data->win, img,
		data->player.x * 64, data->player.y * 64);
}

void	render_tile(t_data *data, int x, int y)
{
	char	tile;
	void	*img;

	tile = data->map.layout[y][x];
	img = NULL;
	if (tile == '1')
		img = data->image.wall;
	else if (tile == 'C')
		img = data->image.collectible;
	else if (tile == 'E')
		img = data->image.exit;
	else if (tile == 'P')
		img = data->image.player_right[0];
	else if (tile == 'X')
	{
		if (data->enemy.direction == 1)
			img = data->image.enemy_right;
		else
			img = data->image.enemy_left;
	}
	if (img)
		mlx_put_image_to_window(data->mlx, data->win, img, x * 64, y * 64);
}

void	render_overlay(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->image.overlay, 10, 10);
	display_moves(data);
}

void	find_enemy(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] == 'X')
			{
				data->enemy.x = x;
				data->enemy.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	game_loop(t_data *data)
{
	static int	frame = 0;

	if (frame++ > 30000)
	{
		move_enemy(data);
		redraw_game(data);
		frame = 0;
	}
	return (0);
}
