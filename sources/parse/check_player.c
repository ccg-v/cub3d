/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:55 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/25 17:16:38 by ccarrace         ###   ########.fr       */
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

int player_count(t_map *map)
{
    int		player_counter;
    char    *valid_directions;

    valid_directions = "NSEW";
    map->i = 0;
	player_counter = 0;
	if (map == NULL || map->array == NULL)
        return (-1);
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
		printf("Error: Map or map array is NULL\n");
		return (FAIL);
	}
    else if (nbr_players == 0)
	{
		printf("Error: No player found in the map\n");
		return (FAIL);
	}
    else if (nbr_players > 1)
	{
		printf("Error: The map contains more than one player\n");
		return (FAIL);
	}
    // else
    //     printf("Map has a valid player\n");
    return (SUCCESS);
}
