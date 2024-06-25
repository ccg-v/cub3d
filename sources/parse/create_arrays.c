/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:05:56 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/25 13:39:32 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	allocate_map_array(t_map *map)
{
	size_t	i;

	map->array = malloc((map->height) * sizeof(char *));
	if (!map->array)
	{
		printf("Error: could not allocate memory for map\n");
		return ;
	}
	i = 0;
	while (i < map->height)
	{
		map->array[i] = malloc((map->width + 1) * sizeof(char));
		if (!map->array[i])
		{
			printf("Error: could not allocate memory for map\n");
			return ;
		}
		i++;
	}
	// return (map->array);
}

static result fill_map_array(t_map *map)
{
    int     fd;
    char    *line;
    size_t  len;

	fd = open_file(map->file);
    if (fd < 0)
        return (FAIL);
    line = get_next_line(fd);
    // map->i = 1;
    // while (map->i < map->starting_line)
    // {
    //     free(line);
    //     line = get_next_line(fd);
    //     map->i++;
    // }
	read_until_line(fd, &line, map->starting_line);
	map->i = 0;
    while (line && map->i < map->height)
    {
        map->j = 0;
        // Ensure line does not contain a newline at the end
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        // Copy characters to map->array, handling shorter lines
        while (map->j < map->width)
        {
            if (map->j < len && line[map->j] != '\0')
                map->array[map->i][map->j] = line[map->j];
            else
                map->array[map->i][map->j] = '\0';
            map->j++;
        }
		map->array[map->i][map->width] = '\0';
        free(line);
        line = get_next_line(fd);
        map->i++;
    }
	// while (line != NULL)
	// {
	// 	free(line);
	// 	line = get_next_line(fd);		
	// }
	read_until_end_of_file(fd, &line);
    free(line);
    close(fd);
    return (SUCCESS);
}

void	allocate_visited_array(t_map *map)
{
    size_t i;

	map->visited_array = malloc((map->height + 2) * sizeof(char *));
	if (!map->visited_array)
	{
		printf("Error: could not allocate memory for visited_map\n");
		return ;
	}
	i = 0;
    while (i < map->height + 2)
	{
        map->visited_array[i] = malloc((map->width + 2) * sizeof(char));
        if (!map->visited_array[i])
		{
			printf("Error: could not allocate memory for visited_map\n");
            while (i > 0)
                free(map->visited_array[--i]);
            free(map->visited_array);
            return;
        }
        ft_memset(map->visited_array[i], ' ', (map->width + 1));
		map->visited_array[i][map->width + 1] = '\0'; // Set the last character to null-terminator
		i++;
    }
}

static void	fill_visited_array(t_map *map)
{
	size_t	i;
	size_t	j;

    i = 0;
	while (i < map->height)
	{
		j = 0;
        while (j < map->width)
		{
            // Copy each character except the null-terminator
            if (map->array[i][j] != '\0')
                map->visited_array[i + 1][j + 1] = map->array[i][j];
            j++;
        }
		i++;
    }
}

result	create_arrays(t_map *map)
{
	allocate_map_array(map);
    if (fill_map_array(map) == FAIL)
		return (FAIL);
	allocate_visited_array(map);
	fill_visited_array(map);
	return (SUCCESS);
}