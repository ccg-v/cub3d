/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/16 14:22:37 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int no_configuration(t_map *map)
// {
//     if (map->starting_line == 1)
//         return (1);
//     return (0);
// }

// int check_configuration_data(t_map *map)
// {
//     if (no_configuration(map))
//         printf("Error: File contains only map\n");
//     return (0);
// }

int is_empty(char *file)
{
	int		fd;
	char 	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: could not open the file\n");
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("Error: file is empty\n");
		close(fd);
		free(line);
		return (1);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("File is NOT empty\n");
	return (0);
}

int	map_is_last(t_map *map)
{
	int		fd;
	char	*line;
	int		map_end_line;
	int		i;
	int		flag;

	flag = 0;
	if (map->starting_line == 1)
	{
		if (map->height == find_file_length(map->file))
			printf("Error: Textures and colors not defined in the file\n");
		else
			printf("Error: Wrong map position (placed first in file)\n");
		return (flag);
	}
	if (map->height == 0)
	{
		printf("Error: No map found in the file\n");
		return (flag);
	}
	fd = open(map->file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: could not open the file\n");
		return (-1);
	}
	line = get_next_line(fd);
	i = 0;
	map_end_line = map->starting_line + map->height;
	while (i < map_end_line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	while (line != NULL && flag == 0)
	{
		if (*line != '\n')
		{
			printf("Error: Wrong map position (not placed last in file)\n");
			flag = 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (flag);
}

int	file_type_is_valid(char *filename, char *expected_extension)
{
	size_t	len;
	char	*file_extension;

	len = ft_strlen(filename);
	file_extension = ft_substr(filename, len - 4, 4);
	if (ft_strncmp(file_extension, expected_extension, 4) != 0)
	{
		free(file_extension);
		return (0);
	}
	free(file_extension);
	return (1);
}