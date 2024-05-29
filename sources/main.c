/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/29 23:52:23 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, char *map_file)
{
	map->file = map_file;
	map->starting_line = 0;
	map->width = 0;
	map->height = 0;	
}

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	init_map(&map, argv[1]);
	map.starting_line = search_map_starting_line(&map);
	// map.height = search_map_height(&map);

printf("map file is %s\n", map.file);
printf("map starting line is %d\n", map.starting_line);
printf("map height is %d\n", map.height);

printf("map height is %d\n", search_map_height(&map));
	return (0);
}