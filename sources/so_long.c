/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:44:10 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/06 16:02:37 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 1);
	ft_memset(data, 0, sizeof(t_data));
	if (init_data(data, ac, av) == -1)
		return (1);
	if (init_mlx_resources(data) == -1)
		return (1);
	gameplay(data);
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (ac != 2 || check_map_name(av[1]))
		return (free_on_error(data, "Invalid arguments or map name\n"));
	get_map(&data->map, av[1]);
	find_player(data);
	find_enemy(data);
	init_flags(&data->flags, data);
	if (check_map(data, &data->flags) == -1)
		return (free_on_error(data, "Map is not valid\n"));
	if (validate_flood_fill(data) == -1)
		return (free_on_error(data, "Map is not valid\n"));
	return (0);
}

int	init_mlx_resources(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_on_error(data, "Failed to initialize MXL\n"));
	mlx_get_screen_size(data->mlx, &data->screen_width, &data->screen_height);
	if (data->map.width > data->screen_width
		|| data->map.height > data->screen_height)
		return (free_on_error(data, "Map it's too big\n"));
	data->win = mlx_new_window(data->mlx, data->map.width, data->map.height,
			"so_long");
	if (!data->win)
		return (ft_putstr_fd("Error\nFailed to create window\n", 2), -1);
	if (load_images(data) == -1)
		return (ft_putstr_fd("Error\nFailed to load images\n", 2), -1);
	return (0);
}

int	load_images(t_data *data)
{
	if (load_player_images(data) == -1 || load_enemy_images(data) == -1
		|| load_environment_images(data) == -1)
		return (-1);
	return (0);
}

int	load_player_images(t_data *data)
{
	int	img_width;
	int	img_height;

	data->image.player_right[0] = mlx_xpm_file_to_image(data->mlx,
			PLAYER_RIGHT, &img_width, &img_height);
	data->image.player_right[1] = mlx_xpm_file_to_image(data->mlx,
			PLAYER_RIGHT1, &img_width, &img_height);
	data->image.player_left[0] = mlx_xpm_file_to_image(data->mlx,
			PLAYER_LEFT, &img_width, &img_height);
	data->image.player_left[1] = mlx_xpm_file_to_image(data->mlx,
			PLAYER_LEFT1, &img_width, &img_height);
	if (!data->image.player_right[0] || !data->image.player_right[1]
		|| !data->image.player_left[0] || !data->image.player_left[1])
		return (-1);
	return (0);
}
