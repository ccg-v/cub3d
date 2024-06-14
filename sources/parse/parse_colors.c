/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:28:00 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/14 23:51:49 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_rgb_array(char **rgb_array, int *color)
{
	int	i;

	i = 0;
	while (rgb_array[i] != NULL && ft_strncmp(rgb_array[i], "\n", 1) && i < 3)
	{
		if (!(is_valid_number(rgb_array[i])))
		{
			printf("Error: Invalid RGB color (negative or non-numeric characters found)\n");
			return (0);
		}
		color[i] = ft_atoi(rgb_array[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Error: Invalid RGB color (parameter out of range found)\n");
			return (0);
		}
		i++;
	}
	if (i != 3 || rgb_array[i] != NULL)
	{
		printf("Error: Invalid RGB color (must have three parameters)\n");
		return (0);
	}
	return (1);
}

int	store_rgb_color(const char *line, int *color)
{
	char	**rgb_array;

	rgb_array = ft_split(line, ',');
	if (!rgb_array)
	{
		printf("Error: Failed to split RGB values.\n");
		return (0);
	}
	if (!valid_rgb_array(rgb_array, color))
	{
		free_rgb_values(rgb_array);
		return (0);
	}
	free_rgb_values(rgb_array);
	return (1);
}

int	check_colors(int *color_found)
{
	if (*color_found == 0)
	{
		printf("Error: No colors defined in the file\n");
		return (-1);
	}
	else if (*color_found == 1)
	{
		printf("Error: Color for the ceiling is wrong or missing\n");
		return (-1);
	}
	else if (*color_found == 2)
	{
		printf("Error: Color for the floor is wrong or missing\n");
		return (-1);
	}
	else if (*color_found == 3)
	{
		printf("Colors ok!\n");
		return (0);
	}
	else
		printf("Error: Too many colors defined in the file\n");
	return (-1);
}

void	process_color_line(t_colors *colors, char *line, int *colors_found)
{
	char	surface;

	surface = *line;
	line++;
	while (*line == ' ' && *line != '\n')
		line++;
	if (surface == 'F')
	{
		if (store_rgb_color(line, colors->floor))
			*colors_found += 1;
	}
	else if (surface == 'C')
	{
		if (store_rgb_color(line, colors->ceiling))
			*colors_found += 2;
	}
}

int	parse_colors(t_map *map, t_colors *colors)
{
	int		fd;
	char	*line;
	char	*original_line;
	int		colors_found;

	fd = open_file(map->file);
	colors_found = 0;
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		original_line = line;
		if (*line == 'F' || *line == 'C')
			process_color_line(colors, line, &colors_found);
		free(original_line);
		line = get_next_line(fd);
	}
	close(fd);
	check_colors(&colors_found);
	return (0);
}
