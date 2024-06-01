/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_check_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:00:12 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/02 01:19:26 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	round_completed(size_t i, size_t j, size_t starting_i, size_t starting_j)
{
	if (i == starting_i && j == starting_j)
	{
		printf("Round completed. The map is closed.\n");
		return (1);
	}
	printf("Map is NOT closed\n");
	return (0);
}

int check_borders(t_map *map) {
    size_t	i;
	size_t	j;

	size_t	starting_i;
	size_t	starting_j;

	i = 0;
	j = 0;
	
    // Find starting position
    while (map->array[i][j] == ' ' && map->array[i][j] != '\0')
        j++;
    starting_i = i;
    starting_j = j;

    // Check right position
    while (map->array[i][++j] == '1' && j < map->width - 2) {
        if (round_completed(i, j, starting_i, starting_j))
            return 1;
    }
    // Check down position
    while (map->array[++i][j] == '1' && i < (map->height - 1)) {
        if (round_completed(i, j, starting_i, starting_j))
            return 1;
    }
    // Check left position
    while (map->array[i][--j] == '1' && j >= 0) {
        if (round_completed(i, j, starting_i, starting_j))
            return 1;
    }
    // Check up position
    while (map->array[--i][j] == '1') {
        if (round_completed(i, j, starting_i, starting_j))
            return 1;
    }
    return 0;
}


