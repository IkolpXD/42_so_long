/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:58:13 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/05 12:51:31 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_flags(t_flags *flags, t_data *data)
{
	flags->wall = 0;
	flags->player = 0;
	flags->collectible = 0;
	flags->exit = 0;
	flags->enemy = 0;
	flags->errors = 0;
	data->moves = 0;
	data->player.direction = 1;
	data->player.frame = 0;
	data->enemy.direction = 1;
}

void	find_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] == 'P')
			{
				data->player.x = x;
				data->player.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	handle_interations(t_data *data, int new_x, int new_y)
{
	char	next_tile;

	next_tile = data->map.layout[new_y][new_x];
	if (next_tile == 'C')
		data->flags.collectible--;
	if (data->map.layout[data->player.y][data->player.x] != 'E')
		data->map.layout[data->player.y][data->player.x] = '0';
	data->player.x = new_x;
	data->player.y = new_y;
	if (next_tile != 'E')
		data->map.layout[new_y][new_x] = 'P';
	redraw_game(data);
	if (next_tile == 'E' && data->flags.collectible == 0)
		close_window(data);
	if (data->flags.enemy == 1)
	{
		if (data->enemy.x == data->player.x && data->enemy.y == data->player.y)
		{
			ft_putstr_fd("You were caught by the enemy!\n", 1);
			close_window(data);
		}
	}
}

void	display_moves(t_data *data)
{
	int		width;
	int		height;
	char	*moves_str;
	char	*final_str;

	width = 0;
	height = 0;
	moves_str = ft_itoa(data->moves);
	if (!moves_str)
		return ;
	final_str = ft_strjoin("Moves: ", moves_str);
	free(moves_str);
	if (!final_str)
		return ;
	mlx_put_image_to_window(data->mlx, data->win, data->image.overlay, 10, 10);
	mlx_string_put(data->mlx, data->win, 15, 35, 0x000000, final_str);
	free(final_str);
}

int	is_move_key(int keycode)
{
	return (keycode == W || keycode == A || keycode == S
		|| keycode == D || keycode == UP || keycode == DOWN
		|| keycode == LEFT || keycode == RIGHT);
}
