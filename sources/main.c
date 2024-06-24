/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/24 01:22:28 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

result	check_args(int argc)
{
    if (argc!= 2)
    {
      printf("Error: Wrong arguments (usage: ./cub3d <path_to_file>)\n");
      return (FAIL);
    }
	return (SUCCESS);
}

void	init(char *file_name, t_map *map, t_textures *textures, t_colors *colors)
{
    init_map(map, file_name);
    init_textures(textures);
    init_colors(colors);	
}

int main(int argc, char **argv)
{
    t_map         map;
    t_textures    textures;
    t_colors  colors;

	if (check_args(argc) == FAIL)
		return (FAIL);
	init(argv[1], &map, &textures, &colors);
	if (file_check(argv[1]) == FAIL)
		return (FAIL);

    find_map_starting_line(&map);
	find_map_height(&map);
    find_map_width(&map);
	
	if (check_scene_description(&map) == FAIL)
		return (FAIL);

    allocate_map_array(&map);
    fill_map_array(&map);
    // print_map_array(&map);

	if (check_textures(&map, &textures) == 	FAIL)
		return (FAIL);
    // Free the allocated memory for texture paths
    free(textures.north);
    free(textures.south);
    free(textures.west);
    free(textures.east);
	
    if (check_colors(&map, &colors) == FAIL)
		return (FAIL);

    if (all_chars_are_valid(&map))
      printf("All characters in map are valid\n");
    else
      printf("Error: map contains invalid characters\n");

    check_player(&map);
    printf("Player orientation is %c\n", map.player_orientation);

	allocate_visited_array(&map);

	//	Start the dfs search from the player's position (replace all
	//	walkable cells (that is, zeros) with '@')
	size_t row = map.player_y + 1;
	while (row < (map.height + 2))
	{
		size_t	column = map.player_x + 1;
		while (column < (map.width + 1))
		{
			if (map.visited_array[row][column] != '0')
				dfs(&map, row, column);
			column++;
		}
		row++;
	}

	//	Print visited map
	// for (size_t i = 0; i < (map.height + 2); ++i)
	// 	printf("%s\n", map.visited_array[i]);

	//	Search if the map is closed (all visited cells ('@' should be
	//	adjacent to other visited cells or walls ('@', '1'), never to 
	//	a whitespace)
	if (!is_map_closed(&map))
		printf("Error: Map is not closed\n");
	else
		printf("Map is closed!\n");
		
	//	Search if the map has non-reachable areas in the map (any cell
	//	remaining with zero value after running dfs)
	if (!is_fully_walkable(&map))
		printf("Warning: Map has walkable but non-reachable parts\n");
	else
		printf("Map is fully walkable!\n");

    free_array(map.array, map.height);
	free_array(map.visited_array, (map.height + 2));
    return 0;
}
