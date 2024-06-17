#include "cub3d.h"

// void print_visited_map(t_map *map)
// {
// 	size_t	i = 0;
// 	// int	len = 0;
// 	while (i < map->height)
// 	{
// 		size_t j = 0;
// 		// len = ft_strlen(map->visited[i]);
// 		// while ((int)j < len)
// 		while (j < map->width)
// 		{
// 			printf("%c", map->visited[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

void print_visited_map(t_map *map) {
    printf("Visited Map:\n");
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            printf("%d", map->visited[i][j] ? 1 : 0);
        }
        printf("\n");
    }
}

void	dfs2(t_map *map, int x, int y)
{
	int			i;
	int			nx;
	int			ny;
	static int	dx[] = {0, 0, -1, 1};
	static int	dy[] = {-1, 1, 0, 0};

	if ((int)x <= 0 || (int)y <= 0 || (int)x >= (int)(map->width - 1) || (int)y >= (int)(map->height - 1))
	{
		map->closed = false;
		return ;
	}
	map->visited[y][x] = true;
	map->width = ft_strlen(map->array[y]);
	i = -1;
	while (++i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if ((int)nx >= 0 && (int)ny >= 0 && (int)nx <= (int)map->width && (int)ny <= (int)map->height
			&& !(map->visited[ny][nx]) && map->array[ny][nx] == '0')
			dfs2(map, nx, ny);
	}
}

bool	is_map_closed(t_map *map)
{
	int	i;
	int	j;

	map->visited = ft_calloc(sizeof(char *), map->height);
	if (map->visited == NULL)
		return (false);
	i = -1;
	while (++i < (int)map->height)
	{
		map->visited[i] = ft_calloc(sizeof(char), map->width);
		if (map->visited[i] == NULL)
			return (false);
		j = -1;
		while (++j < (int)map->width)
			map->visited[i][j] = '0';
	}
	map->visited[i][j] = '\0';
printf("0_Visited_map:\n");
print_visited_map(map);
	dfs2(map, map->player_x, map->player_y);
	i = -1;
	while (++i < (int)map->height)
		free(map->visited[i]);
	free(map->visited);
	return (map->closed);
}
