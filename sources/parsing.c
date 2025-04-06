/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:43:42 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/06 16:01:49 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_name(char *av)
{
	int		fd;
	char	*first_dot;
	char	*last_dot;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nInvalid map file\n", 2), 1);
	close (fd);
	first_dot = ft_strchr(av, '.');
	last_dot = ft_strrchr(av, '.');
	if (last_dot == NULL || last_dot == av)
		return (1);
	if (first_dot != last_dot)
		return (1);
	if (ft_strncmp(last_dot, ".ber", 4) != 0)
		return (1);
	return (0);
}

int	validate_flood_fill(t_data *data)
{
	char	**map_copy;
	int		result;

	if (!check_map_format(data))
		return (-1);
	map_copy = copy_map(data->map.layout);
	if (!map_copy)
		return (-1);
	flood_fill(map_copy, data->player.x, data->player.y, data->map.rows);
	result = check_for_collectibles_or_exit(map_copy, data->map.rows,
			data->map.cols);
	free_map(map_copy, data->map.rows);
	return (result);
}

void	flood_fill(char **map, int x, int y, int rows)
{
	int	cols;

	cols = ft_strlen(map[0]);
	if (x < 0 || y < 0 || x >= cols || y >= rows)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, rows);
	flood_fill(map, x - 1, y, rows);
	flood_fill(map, x, y + 1, rows);
	flood_fill(map, x, y - 1, rows);
}

int	check_for_collectibles_or_exit(char **map_copy, int rows, int cols)
{
	int		y;
	int		x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
