/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:28:00 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/03 01:47:26 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int rgb_to_hex(int *rgb_array)
{
    return ((rgb_array[0] & 0xFF) << 24) | ((rgb_array[1] & 0xFF) << 16) | ((rgb_array[2] & 0xFF) << 8) | 0xFF;
}

// static unsigned long rgb_to_hex(int *rgb_array)
// {
// 	return((rgb_array[0] << 16) + (rgb_array[1] << 8) + rgb_array[2]);
// }

// static unsigned long	rgb_to_hex(int *rgb_array)
// {
// 	unsigned long	hex_value;
// 	int				red;
// 	int				green;
// 	int				blue;

// 	red = rgb_array[0];
// 	green = rgb_array[1];
// 	blue = rgb_array[2];
// 	hex_value = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
// printf("hex value is %1lX\n", hex_value);
// 	return (hex_value);
// 	// return (hex_value | 0xFF000000);
// }


static boolean	rgb_triplet_is_valid(char **rgb_array, int *color)
{
	int	i;

	i = 0;
	while (rgb_array[i] != NULL && ft_strncmp(rgb_array[i], "\n", 1) && i < 3)
	{
		if (!(is_valid_number(rgb_array[i])))
		{
			printf("Error: Color: ");
			printf("Negative value or non-numeric characters found\n");
			return (FALSE);
		}
		color[i] = ft_atoi(rgb_array[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Error: Color: Parameter out of range found\n");
			return (FALSE);
		}
		i++;
	}
	if (i != 3 || rgb_array[i] != NULL)
	{
		printf("Error: Color: RGB must have three parameters\n");
		return (FALSE);
	}
	return (TRUE);
}

static result	store_rgb_color(const char *line, int *color)
{
	char	**rgb_array;

	rgb_array = ft_split(line, ',');
	if (!rgb_array)
	{
		printf("Error: Failed to split RGB values.\n");
		return (FAIL);
	}
	if (rgb_triplet_is_valid(rgb_array, color) == FALSE)
	{
		free_rgb_values(rgb_array);
		return (FAIL);
	}

	free_rgb_values(rgb_array);
	return (SUCCESS);
}

static boolean	are_colors_defined(int *color_found)
{
	if (*color_found == 0)
	{
		printf("Error: Colors: Not defined in the file\n");
		return (FALSE);
	}
	else if (*color_found == 1)
	{
		printf("Error: Colors: Ceiling is wrong or missing\n");
		return (FALSE);
	}
	else if (*color_found == 2)
	{
		printf("Error: Colors: Floor is wrong or missing\n");
		return (FALSE);
	}
	else if (*color_found == 3)
		return (TRUE);
	else
		printf("Error: Colors: Only two colors needed\n");
	return (FALSE);
}

static result	process_color_line(t_colors *colors, char *line,
		int *colors_found)
{
	char	surface;

	surface = *line;
	line++;
	while (*line == ' ' && *line != '\n')
		line++;
	if (surface == 'F')
	{
		if (store_rgb_color(line, colors->floor) == SUCCESS)
		{
			*colors_found += 1;
			colors->hex_floor = rgb_to_hex(colors->floor);
		}
		else
			return (FAIL);
	}
	else if (surface == 'C')
	{
		if (store_rgb_color(line, colors->ceiling) == SUCCESS)
		{
			*colors_found += 2;
			colors->hex_ceiling = rgb_to_hex(colors->ceiling);
		}
		else
			return (FAIL);
	}
	return (SUCCESS);
}

boolean	are_colors_unique(t_colors *colors)
{
	if((colors->hex_ceiling) == (colors->hex_floor))
	{
		printf("Error: Colors: must be different for ceiling and floor\n");
		return (FALSE);
	}
	return (TRUE);
}

result	check_colors(t_data *data, t_colors *colors)
{
	int		fd;
	char	*line;
	char	*original_line;
	int		colors_found;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	colors_found = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trim_and_reduce_spaces(line); 
		original_line = line;
		if ((*line == 'F' || *line == 'C')
		&& (process_color_line(colors, line, &colors_found) == FAIL))
			return (FAIL);
		free(original_line);
		line = get_next_line(fd);
	}
	close(fd);
	if (are_colors_defined(&colors_found) == FALSE || are_colors_unique(colors) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
