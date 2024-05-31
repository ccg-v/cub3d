/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/01 01:28:12 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, char *map_file)
{
	map->file = map_file;
	map->starting_line = 1;
	map->width = 0;
	map->height = 0;
	map->i = 0;
	map->j = 0;
}

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	init_map(&map, argv[1]);
	find_map_starting_line_and_height(&map);
	find_map_width(&map);
	allocate_map_array(&map);
	fill_map_array(&map);
	print_map_array(&map);
	free_map_array(&map);

printf("map file is %s\n", map.file);
printf("map starting line is %zu\n", map.starting_line);
printf("map height is %zu\n", map.height);
printf("map width is %zu\n", map.width);
	return (0);
}