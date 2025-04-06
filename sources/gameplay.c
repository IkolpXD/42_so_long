/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:34:19 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/05 12:53:59 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	move_player(int keycode, t_data *data)
{
	int		new_x;
	int		new_y;

	new_x = data->player.x;
	new_y = data->player.y;
	if (keycode == ESC)
		close_window(data);
	if (!is_move_key(keycode))
		return (0);
	set_directions(keycode, data, &new_x, &new_y);
	if (is_valid_move(data, new_x, new_y))
	{
		data->player.frame = (data->player.frame + 1) % 2;
		handle_interations(data, new_x, new_y);
		data->moves++;
		display_moves(data);
	}
	return (0);
}

void	set_directions(int keycode, t_data *data, int *x, int *y)
{
	if (keycode == W || keycode == UP)
		(*y)--;
	else if (keycode == S || keycode == DOWN)
		(*y)++;
	else if (keycode == A || keycode == LEFT)
	{
		(*x)--;
		data->player.direction = 0;
	}
	else if (keycode == D || keycode == RIGHT)
	{
		(*x)++;
		data->player.direction = 1;
	}
}

void	move_enemy(t_data *data)
{
	int		new_x;
	int		y;
	char	next_tile;

	new_x = data->enemy.x + data->enemy.direction;
	y = data->enemy.y;
	next_tile = data->map.layout[y][new_x];
	if (next_tile == '0' || next_tile == 'P')
	{
		if (data->map.layout[y][data->enemy.x] == 'X')
			data->map.layout[y][data->enemy.x] = '0';
		data->enemy.x = new_x;
		data->map.layout[y][new_x] = 'X';
	}
	else if (next_tile == '1' || next_tile == 'C' || next_tile == 'E')
		data->enemy.direction *= -1;
	if (data->enemy.x == data->player.x && data->enemy.y == data->player.y)
	{
		ft_putstr_fd("You were caught by the enemy!\n", 1);
		close_window(data);
	}
}

void	gameplay(t_data *data)
{
	render_map(data);
	mlx_hook(data->win, KeyPress, KeyPressMask, move_player, data);
	if (data->flags.enemy == 1)
		mlx_loop_hook(data->mlx, game_loop, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, close_window, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
}
