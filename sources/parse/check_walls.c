/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:41 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/25 14:56:48 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_visited_map(t_map *map)
{
	size_t	row;
	size_t	column;
	
	map->visited_height = map->height + 2;
	map->visited_width = map->width + 1;	
	row = 0;
	system("clear");
	printf ("Checking map...\n");
	while (row < map->visited_height)
	{
		column = 0;
		while (column < map->visited_width)
		{
			if (map->visited_array[row][column] == '@')
			{
				if ((map->visited_array[row - 1][column] == ' ') || (map->visited_array[row][column + 1] == ' ')
					|| (map->visited_array[row + 1][column] == ' ') || (map->visited_array[row][column - 1] == ' '))
					printf(BACKGROUND_BRIGHT_RED "%c" RESET, map->visited_array[row][column]);				
				else
					printf(BOLD_BRIGHT_GREEN "%c" RESET, map->visited_array[row][column]);
			}
			else if (map->visited_array[row][column] == '0')
				printf(BOLD_BRIGHT_RED "%c" RESET, map->visited_array[row][column]);
			else
				printf("%c", map->visited_array[row][column]);
			column++;			
		}
		row++;
		printf("\n");
	}
}

/*
 *	dfs()
 *
 * 	dfs() is inspired in Depth-First Search, an algorythm used for traversing
 *  or searching through tree or graph data estructures. 
 *  The goal of our dfs() is to mark as visited all the walkable cells in the 
 *  map. To this effect, it traverses recursively the map changing to value '@'
 *	all the visited cells if their value is '0'.
 *  The resultant 'visited_array' stores the map with the walls ('1'), the 
 * 	visited cells ('@') and the non-walkable parts ('0'). It will be used later
 *	to find if map is closed, and if it's fully playable.
 */

void	dfs(t_map *map, int row, int column)
{
	map->visited_height = map->height + 2;
	map->visited_width = map->width + 1;

	if (row < 0
		|| row >= (int)map->visited_height
		|| column < 0
		|| column >= (int)map->visited_width 
		|| map->visited_array[row][column] == ' ' 
		|| map->visited_array[row][column] == '1' 
		|| map->visited_array[row][column] == '@')
		return ;
	map->visited_array[row][column] = '@';
	// usleep(100000);
	// print_visited_map(map);
	dfs(map, row -1, column);
	dfs(map, row, column + 1);
	dfs(map, row + 1, column);
	dfs(map, row, column - 1);
}

/*
 *	start_dfs_search()
 *
 *	Start the dfs search from the player's position (replace all
 *	walkable cells (that is, zeros) with '@')
 */

void	start_dfs_search(t_map *map)
{
	size_t row = map->player_y + 1;
	while (row < (map->height + 2))
	{
		size_t	column = map->player_x + 1;
		while (column < (map->width + 1))
		{
			if (map->visited_array[row][column] != '0')
				dfs(map, row, column);
			column++;
		}
		row++;
	}
}
/*
 *	is_map_closed()
 *
 *	Searches if the map is closed (all visited cells ('@') should be adjacent
 *	to other visited cells or walls ('@', '1'), never to a whitespace)
 */
boolean	is_map_closed(t_map *map)
{
	size_t	row;
	size_t	column;
	
	map->visited_height = map->height + 2;
	map->visited_width = map->width + 1;
	row = 0;
	while (row < map->visited_height)
	{
		column = 0;
		while (column < map->visited_width)
		{
			if (map->visited_array[row][column] == '@')
			{
				if ((row > 0 && map->visited_array[row - 1][column] == ' ')
					|| (row < (map->visited_height - 1) && map->visited_array[row + 1][column] == ' ')
					|| (column > 0 && map->visited_array[row][column - 1] == ' ')
					|| (column < (map->visited_width - 1) && map->visited_array[row][column + 1] == ' '))
					return (FALSE);
			}
			column++;
		}
		row++;
	}
	return (TRUE);
}

/*
 *	is_fully_walkable()
 *
 * 	Search if the map has non-reachable areas in the map (any cell remaining 
 * 	with value '0' after running dfs)
 */
boolean	is_fully_walkable(t_map *map)
{
	size_t	row;
	size_t	column;
	
	map->visited_height = map->height + 2;
	map->visited_width = map->width + 1;
	row = 0;
	while (row < map->visited_height)
	{
		column = 0;
		while (column < map->visited_width)
		{
			if (map->visited_array[row][column] == '0')
					return (FALSE);
			column++;
		}
		row++;
	}
	return (TRUE);
}

result	check_walls(t_map *map)
{
	start_dfs_search(map);
	if (is_map_closed(map) == FALSE)
	{
		printf("Error: Map is not closed\n");
		return (FAIL);
	}
	else if (is_fully_walkable(map) == FALSE)
	{
		printf("Warning: Map has walkable but non-reachable parts\n");
	}
	printf("Map is closed\n");
	printf("All checks passed. Map is valid\n");
	printf("Starting cub3D...\n");
	return (SUCCESS);
}
