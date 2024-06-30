/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/01 00:14:49 by ccarrace         ###   ########.fr       */
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

void	init(char *file_name, t_data *data, t_textures *textures, t_colors *colors)
{
    init_map(data, file_name);
    init_textures(textures);
    init_colors(colors);	
}

int	free_and_exit(t_textures *textures, t_map *map)
{
	free(textures->north);
	free(textures->south);
	free(textures->west);
	free(textures->east);
	free_array(map->array, map->height);
	free_array(map->visited_array, (map->height + 2));
	return (0);
}

int main(int argc, char **argv)
{
    // t_map		map;
    t_textures	textures;
    t_colors	colors;
	t_data		data;

	if (check_args(argc) == FAIL)
		return (FAIL);
	init(argv[1], &data, &textures, &colors);
	if (file_check(argv[1]) == FAIL || find_map_dimensions(&data) == FAIL
	|| check_scene_description(&data) == FAIL || check_colors(&data, &colors) == FAIL)
		return (FAIL);
	// print_map_array(map.array, map.height, map.width);
	if (check_textures(&data, &textures) == 	FAIL)
	{	
		free(textures.north);
		free(textures.south);
		free(textures.west);
		free(textures.east);
		return (FAIL);
	}
	create_arrays(&data);
	if (check_player(&data) == FAIL)
		return (free_and_exit(&textures, &data.map));
	// print_map_array(map.visited_array, map.height + 2, map.width + 1);
	if (check_walls(&data) == FAIL)
		return (free_and_exit(&textures, &data.map));

	for (int i = 0; i < 4; i++)
		printf("%s = %s\n", textures.texture_ids[i], *(textures.paths_array[i]));

	// engine_main(&data, &textures);
	free_array(data.map.array, data.map.height);
	free_array(data.map.visited_array, (data.map.height + 2));
    return (0);
}
