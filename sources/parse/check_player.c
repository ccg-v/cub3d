/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:55 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/21 23:08:45 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int all_chars_are_valid(t_map *map)
{
    char    *valid_chars;

    valid_chars = "NSEW10 ";
    map->i = 0;
	if (map == NULL || map->array == NULL)
        return (-1);
    while (map->i < map->height)
    {
        map->j = 0;
        while (map->array[map->i][map->j] != '\0')
        {
            if (!ft_strchr(valid_chars, map->array[map->i][map->j]))
                return (0);
            map->j++;
        }
        map->i++;
    }
	return (1);    
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

int check_player(t_map *map)
{
    int nbr_players;

    nbr_players = player_count(map);
    if (nbr_players == -1)
		printf("Error: map or map->array is NULL\n");
    else if (nbr_players == 0)
		printf("Error: no player found in the map\n");
    else if (nbr_players > 1)
		printf("Error: the map contains more than one player\n");
    else
        printf("Map has a valid player\n");
    return (0);
}



