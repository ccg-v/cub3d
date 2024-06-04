/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_check_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:00:12 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/04 20:24:03 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void dfs(t_map *map, size_t x, size_t y) {
//     // Base cases: out-of-bounds, already visited, or wall
//     if (x < 0 || x >= map->width || y < 0 || y >= map->height || map->visited[y][x] || map->array[y][x] == '1') {
//         return;
//     }

//     // Mark the current cell as visited
//     map->visited[y][x] = true;

//     // Recursively visit neighboring cells
//     dfs(map, x + 1, y);
//     dfs(map, x - 1, y);
//     dfs(map, x, y + 1);
//     dfs(map, x, y - 1);
// }

// void	dfs(t_map *map, size_t x, size_t y)	// Depth-First Search
// {
// 	size_t		i;
// 	size_t		new_x;
// 	size_t		new_y;
// 	static int	dx[] = {0, 0, -1, 1}; // Changes in x for moving up, down, left, right
// 	static int	dy[] = {-1, 1, 0, 0}; // Changes in y for moving up, down, left, right

// 	// Return if cell is out-of-bounds, already visited or a wall
// 	if (x < 0 || y < 0 || x >= (map->width) || y >= (map->height))
// 	{
// 		map->closed = false;
// 		return ;
// 	}

// 	// Mark the current cell as visited
// 	map->visited[y][x] = true;

// 	// Update the width to match the length of the current row of the map
// 	map->width = ft_strlen(map->array[y]);

//     // Iterate over all four possible directions
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		new_x = x + dx[i]; // Calculate the new x position
// 		new_y = y + dy[i]; // Calculate the new y position 

// 		// Check if the new position is valid and not yet visited, and if it's a navigable cell
// 		if (new_x >= 0 && new_y >= 0 && new_x <= map->width && new_y <= map->height
// 			&& !(map->visited[new_y][new_x]) && map->array[new_y][new_x] == '0')
// 			dfs(map, new_x, new_y);	// Recursively call DFS for the new position
// 	}
// }

// void dfs(t_map *map, size_t x, size_t y) // Depth-First Search
// {
//     size_t i;
//     size_t new_x;
//     size_t new_y;
//     static int dx[] = {0, 0, -1, 1}; // Changes in x for moving up, down, left, right
//     static int dy[] = {-1, 1, 0, 0}; // Changes in y for moving up, down, left, right

//     // Corrected boundary check
//     if (x < 0 || y < 0 || x >= map->width || y >= map->height)
//     {
//         map->closed = false;
//         return;
//     }
    
//     map->visited[y][x] = true;

//     for (i = 0; i < 4; ++i)
//     {
//         new_x = x + dx[i];
//         new_y = y + dy[i];
//         if (new_x >= 0 && new_y >= 0 && new_x < map->width && new_y < map->height
//             && !map->visited[new_y][new_x] && map->array[new_y][new_x] == '0')
//         {
//             dfs(map, new_x, new_y);
//         }
//     }
// }

void dfs(t_map *map, size_t x, size_t y) // Keep original types for function parameters
{
    int i;
    int new_x;
    int new_y;
    static int dx[] = {0, 0, -1, 1}; // Changes in x for moving up, down, left, right
    static int dy[] = {-1, 1, 0, 0}; // Changes in y for moving up, down, left, right

    // Corrected boundary check with casted coordinates
    if ((int)x < 0 || (int)y < 0 || (int)x >= (int)map->width || (int)y >= (int)map->height)
    {
        map->closed = false;
        return;
    }
    
    map->visited[y][x] = true;

    for (i = 0; i < 4; ++i)
    {
        new_x = (int)x + dx[i];
        new_y = (int)y + dy[i];
        if (new_x >= 0 && new_y >= 0 && new_x < (int)map->width && new_y < (int)map->height
            && !map->visited[new_y][new_x] && map->array[new_y][new_x] == '1')
        {
            dfs(map, (size_t)new_x, (size_t)new_y);
        }
    }

	printf("\nVisited map:\n");
	size_t k = 0;
	while (map->visited[k])
	{
		size_t j = 0;
		while (j < ft_strlen(map->visited[k]))
		{
			printf("%c", map->array[k][j]);
			j++;
		}
		printf("\n");
		k++;
	}
}

bool	check_navigability(t_map *map)
{
	size_t	i;
	size_t	j;

	map->visited = ft_calloc(sizeof(char *), map->height);
	if (map->visited == NULL)
		return (false);
	i = -1;
	while (++i < map->height)
	{
		map->visited[i] = ft_calloc(sizeof(char), map->width);
		if (map->visited[i] == NULL)
			return (false);
		j = -1;
		while (++j < map->width)
			map->visited[i][j] = false;
	}
	dfs(map, map->player_x, map->player_y);
	i = -1;
	while (++i < map->height)
		free(map->visited[i]);
	free(map->visited);
	return (map->closed);
}


