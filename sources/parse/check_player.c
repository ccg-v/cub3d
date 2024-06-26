/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:55 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/26 17:41:47 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

boolean all_chars_are_valid(t_map *map)
{
    char    *valid_chars;
	size_t	i;
	size_t	j;
	
    valid_chars = "NSEW10 ";
    i = 0;
	if (map == NULL || map->array == NULL)
	{
		printf("Error: Map or map array is NULL\n");
        return (FALSE);
	}
    while (i < map->height)
    {
        j = 0;
        while (map->array[i][j] != '\0')
        {
            if (!ft_strchr(valid_chars, map->array[i][j]))
                return (FALSE);
            j++;
        }
        i++;
    }
	return (TRUE);    
}

// boolean	is_player_on_edge(t_map *map)
// {
// 	if (map->player_x == 0
// 		|| map->player_y == 0
// 		|| map->player_x == map->width - 2
// 		|| map->player_y == map->height - 1
// 		|| map->visited_array[map->player_x][map->player_y + 1] == ' '	// left
// 		|| map->visited_array[map->player_x][map->player_y + 3] == ' '	// right
// 		|| map->visited_array[map->player_x - 1][map->player_y + 2] == ' '	// up
// 		|| map->visited_array[map->player_x + 1][map->player_y + 2] == ' ')	// down
// 		return (TRUE);
// 	return (FALSE);
// }

// boolean	is_player_on_edge(t_map *map)
// {
// 	if (map->player_x == 0
// 		|| map->player_y == 0
// 		|| map->player_x == map->width - 2
// 		|| map->player_y == map->height - 1
// 		|| (map->player_y > 0 && map->array[map->player_x - 1][map->player_y] == ' ')	// left
// 		|| (map->player_y < map->width && map->array[map->player_x + 1][map->player_y] == ' ')	// right
// 		|| (map->player_x > 0 && map->array[map->player_x][map->player_y - 1] == ' ')	// up
// 		|| (map->player_x < map->height && map->array[map->player_x][map->player_y + 1] == ' '))	// down
// 		return (TRUE);
// 	return (FALSE);
// }
boolean is_player_on_edge(t_map *map)
{
    if (map->player_x == 0  // Left edge
        || map->player_x == map->width - 2  // Right edge
        || map->player_y == 0  // Top edge
        || map->player_y == map->height - 1  // Bottom edge
        || (map->player_x > 0 && map->array[map->player_y][map->player_x - 1] == ' ')  // Left empty space
        || (map->player_x < map->width - 2 && map->array[map->player_y][map->player_x + 1] == ' ')  // Right empty space
        || (map->player_y > 0 && map->array[map->player_y - 1][map->player_x] == ' ')  // Top empty space
        || (map->player_y < map->height - 1 && map->array[map->player_y + 1][map->player_x] == ' '))  // Bottom empty space
        return (TRUE);
    return (FALSE);
}

int player_count(t_map *map)
{
    int		player_counter;
    char    *valid_directions;

    valid_directions = "NSEW";
    map->i = 0;
	player_counter = 0;
	if (map == NULL || map->array == NULL)
	{
		printf("Error: Map or map array is NULL\n");
        return (0);
	}
    while (map->i < map->height)
    {
        map->j = 0;
        while (map->array[map->i][map->j] != '\0')
        {
            if (ft_strchr(valid_directions, map->array[map->i][map->j]))
            {
                map->player_orientation = map->array[map->i][map->j];
				map->player_x = map->j;
				map->player_y = map->i;
				if (is_player_on_edge(map))
					return (-1);
                player_counter++;
            }
            map->j++;
        }
        map->i++;
    }
	return (player_counter);
}

result check_player(t_map *map)
{
    int nbr_players;

    if (all_chars_are_valid(map) == FALSE)
	{
		printf("Error: Map contains invalid characters\n");
		return (FAIL);
	}
    nbr_players = player_count(map);
    if (nbr_players == -1)
	{
		printf("Error: Player cannot be placed in a map edge\n");
		return (FAIL);
	}
    if (nbr_players == 0) //|| (is_player_on_edge(map) == TRUE)) 
	{
		printf("Error: No player found inside the map\n");
		return (FAIL);
	}
    if (nbr_players > 1)
	{
		printf("Error: The map contains more than one player\n");
		return (FAIL);
	}
	// if (is_player_on_edge(map) == TRUE)
	// {
	// 	printf("Error: Player is not inside the map\n");
	// 	return (FAIL);
	// }
    return (SUCCESS);
}
