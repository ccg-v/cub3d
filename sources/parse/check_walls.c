#include "cub3d.h"

void	print_visited_map(t_map *map)
{
	size_t	row;
	size_t	column;
	size_t	visited_height;
	size_t	visited_width;
	
	visited_height = map->height + 2;
	visited_width = map->width + 1;	
	row = 0;
	system("clear");
	printf ("Checking map...\n");
	while (row < visited_height)
	{
		column = 0;
		while (column < visited_width)
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

void	dfs(t_map *map, int row, int column)
{
	int visited_height;
	int visited_width;
	
	visited_height = map->height + 2;
	visited_width = map->width + 1;

	if ( row < 0 || row >= visited_height || column < 0 || column >= visited_width 
		|| map->visited_array[row][column] == ' ' 
		|| map->visited_array[row][column] == '1' 
		|| map->visited_array[row][column] == '@' )
		return;

	map->visited_array[row][column] = '@';
	// usleep(100000);
	// print_visited_map(map);
	
	dfs(map, row -1, column);
	dfs(map, row, column + 1);
	dfs(map, row + 1, column);
	dfs(map, row, column - 1);
}

int	is_map_closed(t_map *map)
{
	size_t	row;
	size_t	column;
	size_t	visited_height;
	size_t	visited_width;
	
	visited_height = map->height + 2;
	visited_width = map->width + 1;
	row = 0;
	while (row < visited_height)
	{
		column = 0;
		while (column < visited_width)
		{
			if (map->visited_array[row][column] == '@')
			{
				if ((row > 0 && map->visited_array[row - 1][column] == ' ')
					|| (row < (visited_height - 1) && map->visited_array[row + 1][column] == ' ')
					|| (column > 0 && map->visited_array[row][column - 1] == ' ')
					|| (column < (visited_width - 1) && map->visited_array[row][column + 1] == ' '))
					return (0);
			}
			column++;
		}
		row++;
	}
	return (1);
}

int	is_fully_walkable(t_map *map)
{
	size_t	row;
	size_t	column;
	size_t	visited_height;
	size_t	visited_width;
	
	visited_height = map->height + 2;
	visited_width = map->width + 1;
	row = 0;
	while (row < visited_height)
	{
		column = 0;
		while (column < visited_width)
		{
			if (map->visited_array[row][column] == '0')
					return (0);
			column++;
		}
		row++;
	}
	return (1);
}
