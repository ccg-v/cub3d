/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/31 02:12:05 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
    }
    return fd;
}

int	find_map_starting_line_and_height(t_map *map)
{
	int		fd;
	char	*line;

	fd = open_file(map->file);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{

		if (((line[0] != ' ' && line[0] != '1')
			|| (line[0] == ' ' &&  ft_strchr(line, '1') == NULL))
			&& map->height == 0)
				++map->starting_line;
		else
		{
			if (line[0] != '\n')
				map->height++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}

int	find_map_width(t_map *map)
{
	int		fd;
	char	*line;

	fd = open_file(map->file);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
    while (line != NULL) {
		free(line);
		if (ft_strlen(line) > map->width)
        	map->width = ft_strlen(line);
		line = get_next_line(fd);
    }
	close(fd);
	free(line);
	return (0);
}

char **allocate_map_array(t_map *map)
{
	size_t	i;

	map->array = ft_calloc((map->height + 1), sizeof(char *));
	if (!map->array)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->array[i] = ft_calloc((map->width + 1) , sizeof(char));
		if (!map->array[i])
			return (NULL);
		i++;
	}
	return (map->array);
}

int	fill_map_array(t_map *map)
{
	int		fd;
	char	*line;
	size_t	i;
	size_t	j;
	size_t	k;

	fd = open_file(map->file);
	if (fd == -1)
		return (-1);
	i = 1;
	k = 0;
	line = get_next_line(fd);
	while (i < map->starting_line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	while (k < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (line[j])
				map->array[k][j] = line[j];
			j++;
		}
		free(line);
		line = get_next_line(fd);
		k++;
	}
	free(line);
	close(fd);
	return (0);
}


//	// NOT NEEDED: height is calculated in search_map_starting_line_and_height()
// int	search_map_height(t_map *map)
// {
// 	int		fd;
// 	int 	current_line;
// 	char	*line;

// 	fd = open_file(map->file);
// 	if (fd == -1)
// 		return (-1);
// 	current_line = 0;
// 	line = get_next_line(fd);
//     while (current_line < map->starting_line && line != NULL)
// 	{
//         free(line);
//         current_line++;
//         if (current_line < map->starting_line) {
//             line = get_next_line(fd);
//         }
//     }
//     while (line != NULL) {
// 		if (line[0] != '\n')
//         	map->height++;
// 		line = get_next_line(fd);
// 		free(line);
//     }
//     close(fd);
// 	return (0);
// }
