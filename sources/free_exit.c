/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:40:00 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/06 16:01:27 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	free_on_error(t_data *data, char *message)
{
	if (data)
	{
		if (data->map.layout)
			free_map(data->map.layout, data->map.rows);
	}
	free(data);
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	return (-1);
}

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < rows)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

int	close_window(t_data *data)
{
	free_map(data->map.layout, data->map.rows);
	mlx_destroy_image(data->mlx, data->image.wall);
	mlx_destroy_image(data->mlx, data->image.exit);
	mlx_destroy_image(data->mlx, data->image.player_right[0]);
	mlx_destroy_image(data->mlx, data->image.player_right[1]);
	mlx_destroy_image(data->mlx, data->image.player_left[0]);
	mlx_destroy_image(data->mlx, data->image.player_left[1]);
	mlx_destroy_image(data->mlx, data->image.enemy_right);
	mlx_destroy_image(data->mlx, data->image.enemy_left);
	mlx_destroy_image(data->mlx, data->image.collectible);
	mlx_destroy_image(data->mlx, data->image.overlay);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}
