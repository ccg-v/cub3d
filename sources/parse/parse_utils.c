/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:30:37 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/22 22:45:36 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(const char *file)
{
    int fd;
	
	fd = open(file, O_RDONLY);
    if (fd == -1)
		return (-1);
    return fd;
}

// void	free_map_array(t_map *map)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < map->height)
// 	{
// 		// printf("freeing map->array[%zu] = '%s'\n", i, map->array[i]);
// 		free(map->array[i]);
// 		i++;
// 	}
// 	free(map->array);
// }

void	free_array(char **array, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_rgb_values(char **rgb_array)
{
	int	i;

	i = 0;
	while (rgb_array[i] != NULL)
	{
		free(rgb_array[i]);
		i++;
	}
	free(rgb_array);
}

int is_valid_number(const char *str)
{
    if (*str == '\0')
        return (0);
    while (*str)
    {
        if (!ft_isdigit((unsigned char)*str) && *str != '\n')
            return (0);
        str++;
    }
    return (1);
}

size_t	find_file_length(char *file)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: could not open the file\n");
		return (-1);
	}
	len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		len++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (len);
}
