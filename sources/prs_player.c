/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:55 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/04 14:43:08 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	check_player(t_map *map)
// {
//     int		i;
//     int		j;
//     int		player_counter;

//     i = 0;
// 	player_counter = 0;
// 	if (map == NULL || map->array == NULL)
// 	{
// 		printf("Error: map or map->array is NULL\n");
//         return (-1);
// 	}
//     while (map->array[i] != NULL)
//     {
// 		printf("Checking row %d: %s\n", i, map->array[i]);
//         j = 0;
//         while (map->array[i][j] != '\0')
// 		{
// 			printf("Checking index %d: %c\n", j, map->array[i][j]);
// 			if (map->array[i][j] == 'N' || map->array[i][j] == 'S' 
// 					|| map->array[i][j] == 'E' || map->array[i][j] == 'W')
// 			{
// 				player_counter++;;
// 				printf("Player counter = %d\n", player_counter);
// 			}
// 			j++;
// 		}
// 		i++;
//     }
// 	return (player_counter);
// 	if (player_counter == 0)
// 		printf("Error: no player found\n");
// 	else if (player_counter > 1)
// 		printf("Error: too many players found\n");
// 	else
// 		printf("Number of players OK\n");
// 	return (0);
// }

int	check_player(t_map *map)
{
    size_t		i;
    int		j;
    int		player_counter;

    i = 0;
	player_counter = 0;
	if (map == NULL || map->array == NULL)
	{
		printf("Error: map or map->array is NULL\n");
        return (-1);
	}
    while (i < map->height)
    {
        j = 0;
        while (map->array[i][j] != '\0')
        {
            if (map->array[i][j] == 'N' || map->array[i][j] == 'S' 
                || map->array[i][j] == 'E' || map->array[i][j] == 'W')
            {
                player_counter++;
            }
            j++;
        }
        i++;
    }
	// return (player_counter);
	printf("NUMBER OF PLAYERS: %d\n", player_counter);
	if (player_counter == 0)
		printf("Error: no player found in the map\n");
	else if (player_counter > 1)
		printf("Error: the map contains more than one player\n");
	else
		printf("Player OK\n");
	return (0);
}
