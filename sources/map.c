/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-jes <made-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:10:29 by made-jes          #+#    #+#             */
/*   Updated: 2025/03/23 21:58:32 by made-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*read_map_layout(int fd)
{
	char	*layout;
	char	*line;
	char	*temp;

	layout = ft_strdup("");
	if (!layout)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = layout;
		layout = ft_strjoin(layout, line);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	return (layout);
}

void	get_map(t_map *map, char *av)
{
	int		fd;
	char	*layout;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return ;
	layout = read_map_layout(fd);
	if (!layout)
		return ;
	map->layout = ft_split(layout, '\n');
	free (layout);
	close (fd);
	i = 0;
	while (map->layout[i])
		i++;
	map->rows = i;
	map->cols = ft_strlen(map->layout[0]);
	map->width = map->cols * 64;
	map->height = map->rows * 64;
}

char	**copy_map(char **original)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (original[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	while (j < i)
	{
		copy[j] = ft_strdup(original[j]);
		if (!copy[j])
		{
			while (j-- > 0)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

void	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			render_tile(data, x, y);
			x++;
		}
		y++;
	}
	render_overlay(data);
}
