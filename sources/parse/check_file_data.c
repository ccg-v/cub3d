/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/15 21:30:28 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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