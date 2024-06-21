/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/22 01:17:25 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, char *map_file)
{
	map->file = map_file;
	map->starting_line = 1;
	map->ending_line = 1;
	map->width = 0;
	map->height = 0;
	map->array = NULL;
	map->i = 0;
	map->j = 0;
	map->visited_array = NULL;
	map->player_x = 0;
	map->player_y = 0;
	map->closed = true;
	map->new_x = 0;
	map->new_y = 0;
}

void  init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->texture_ids[0] = "NO";
	textures->texture_ids[1] = "SO";
	textures->texture_ids[2] = "EA";
	textures->texture_ids[3] = "WE";
	textures->paths_array[0] = &textures->north;
	textures->paths_array[1] = &textures->south;
	textures->paths_array[2] = &textures->east;
	textures->paths_array[3] = &textures->west;	
}

void  init_colors(t_colors *colors)
{
  colors->floor[0] = -1;
  colors->floor[1] = -1;
  colors->floor[2] = -1;
  colors->ceiling[0] = -1; 
  colors->ceiling[1] = -1;
  colors->ceiling[2] = -1;
}

// int	main(int argc, char **argv)
// {
// 	t_map	map;

// 	(void)argc;
// 	init_map(&map, argv[1]);
// 	find_map_starting_line_and_height(&map);
// 	find_map_width(&map);
// 	allocate_map_array(&map);
// 	fill_map_array(&map);
// 	print_map_array(&map);

// printf("Number of players: %d\n", check_player(&map));

// 	// if (check_navigability(&map))
// 	// 	printf("Map is closed and reachable\n");
// 	// else
// 	// 	printf("Map is not closed\n");

// printf("map file is %s\n", map.file);
// printf("map starting line is %zu\n", map.starting_line);
// printf("map height is %zu\n", map.height);
// printf("map width is %zu\n", map.width);

// 	free_map_array(&map);
// 	return (0);
// }


int check_is_dir(char *str)
{
    int fd;

	fd = open(str, O_DIRECTORY);
	printf("fd = %d\n", fd);
	if (fd < 0)
	{
		printf("%s is a file\n", str);
		return (1);
	}
	printf("Error: %s is a directory, not a file\n", str);
	close(fd);
    return (0);
}

int main(int argc, char **argv)
{
    t_map         map;
    t_textures    textures;
    t_colors  colors;

    if (argc!= 2)
    {
      printf("Error: Wrong arguments (usage: ./cub3d <path_to_file>)\n");
      return (0);
    }
    init_map(&map, argv[1]);
    init_textures(&textures);
    init_colors(&colors);
	check_is_dir(argv[1]);
	if (!file_type_is_valid(argv[1], ".cub"))
	{
		printf("Error: Wrong file type (must be .cub)\n");
		exit(-1);
	}
	if (is_empty(map.file))
		return (-1);
    find_map_starting_line(&map);
	find_map_height(&map);
	map_is_last(&map);
    find_map_width(&map);
    allocate_map_array(&map);
    fill_map_array(&map);
    print_map_array(&map);

    parse_textures(&map, &textures);
    check_textures_in_file(&textures);
	check_textures_path(&textures);
    parse_colors(&map, &colors);

    // printf("North texture: %s\n", textures.north);
    // printf("South texture: %s\n", textures.south);
    // printf("West texture: %s\n", textures.west);
    // printf("East texture: %s\n", textures.east);
    // printf("Floor color: %d,%d,%d\n", colors.floor[0], colors.floor[1], colors.floor[2]);
    // printf("Ceiling color: %d,%d,%d\n", colors.ceiling[0], colors.ceiling[1], colors.ceiling[2]);

    // Free the allocated memory for texture paths
    free(textures.north);
    free(textures.south);
    free(textures.west);
    free(textures.east);
	

    if (all_chars_are_valid(&map))
      printf("All characters in map are valid\n");
    else
      printf("Error: map contains invalid characters\n");
    check_player(&map);
printf("Player's row (y) = %ld; Player's column (x) = %ld\n", map.player_y, map.player_x);	
printf("Player position is (%ld, %ld)\n", map.player_y, map.player_x);
    // check_configuration_data(&map);
    printf("Player orientation is %c\n", map.player_orientation);

	// if (is_map_closed(&map))
	// 	printf("Map is closed and walkable\n");
	// else
	// 	printf("Map is not closed\n");
	// printf("\n1_Visited map:\n");
	// print_visited_map(&map);

	// if (check_navigability(&map))
	// 	printf("Map is closed and reachable\n");
	// else
	// 	printf("Map is not closed\n");



	allocate_visited_array(&map);

	//	Start the dfs search from the player's position (replace all
	//	walkable cells (that is, zeros) with '@')
	size_t row = map.player_y + 1;
	while (row < (map.height + 2))
	{
		size_t	column = map.player_x + 1;
		while (column < (map.width + 1))
		{
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
		printf("Warning: Map has non-reachable areas\n");
	else
		printf("Map is fully walkable!\n");
		
    free_map_array(&map);
    return 0;
}
