/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:30:37 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/06 19:55:56 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
    }
    return fd;
}

void free_map_array(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		// printf("freeing map->array[%zu] = '%s'\n", i, map->array[i]);
		free(map->array[i]);
		i++;
	}

	free(map->array);
}