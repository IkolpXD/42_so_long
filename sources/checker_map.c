/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:58:13 by made-jes          #+#    #+#             */
/*   Updated: 2025/04/06 14:19:07 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map(t_data *data, t_flags *flags)
{
	check_objects(flags, data);
	if (flags->collectible < 1 || flags->player != 1
		|| flags->exit != 1 || flags->errors == -1 || flags->enemy > 1)
		return (-1);
	if (check_map_format(data) == -1)
		return (-1);
	if (check_limits(data) == -1)
		return (-1);
	if (validate_flood_fill(data) == -1)
		return (-1);
	return (0);
}

void	check_objects(t_flags *flags, t_data *data)
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
				flags->player++;
			else if (data->map.layout[y][x] == 'C')
				flags->collectible++;
			else if (data->map.layout[y][x] == 'E')
				flags->exit++;
			else if (data->map.layout[y][x] == 'X')
				flags->enemy++;
			else if (data->map.layout[y][x] != '1'
					&& data->map.layout[y][x] != '0')
				flags->errors = -1;
			x++;
		}
		y++;
	}
}

int	check_map_format(t_data *data)
{
	int				i;
	unsigned int	len;

	len = ft_strlen(data->map.layout[0]);
	i = 1;
	while (data->map.layout[i])
	{
		if (ft_strlen(data->map.layout[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

int	check_limits(t_data *data)
{
	int	y;

	y = 0;
	if (check_row(data->map.layout[y], '1') == -1)
		return (-1);
	y++;
	while (data->map.layout[y + 1] != NULL)
	{
		if (data->map.layout[y][0] != '1'
				|| data->map.layout[y][data->map.cols - 1] != '1')
			return (-1);
		y++;
	}
	if (check_row(data->map.layout[y], '1') == -1)
		return (-1);
	return (0);
}

int	check_row(char *row, char wall)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] != wall)
			return (-1);
		i++;
	}
	return (0);
}
