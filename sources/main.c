/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/16 00:34:08 by ccarrace         ###   ########.fr       */
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
	map->visited = NULL;
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
		printf("Error: Wrong file type (must be .cub)\n");
	if (is_empty(map.file))
		return (-1);
    find_map_starting_line(&map);
	find_map_height(&map);
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
    // check_configuration_data(&map);
    printf("Player orientation is %c\n", map.player_orientation);
    
    free_map_array(&map);
    return 0;
}
