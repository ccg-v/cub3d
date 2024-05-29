/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/30 00:27:56 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	IN PROCESS: trying to read file until the end
int	search_map_starting_line(t_map *map)
{
	int		fd;
	char	*line;
	int		map_starting_line;

	fd = open(map->file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	map_starting_line = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{

		if (((line[0] != ' ' && line[0] != '1')
			|| (line[0] == ' ' &&  ft_strchr(line, '1') == NULL))
			&& map->height == 0)
				++map_starting_line;
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
	return (map_starting_line);
}

// //	WORKS but leaves fd pointer in map_starting_line
// int	search_map_starting_line(t_map *map)
// {
// 	int		fd;
// 	char	*line;
// 	int		map_starting_line;

// 	fd = open(map->file, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (-1);
// 	}
// 	map_starting_line = 0;
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		map_starting_line++;
// 		if (line[0] == ' ' && ft_strchr(line, '1') != NULL)
// 		{
// 			free(line);
// 			close(fd);
// 			return (map_starting_line);
// 		}
// 		if (line[0] == '1')
// 			break ;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// 	return (map_starting_line);
// }

int	search_map_height(t_map *map)
{
	int		height;
	int		fd;
	int 	current_line;
	char	*line;

	fd = open(map->file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	current_line = 0;
	height = 0;
	line = get_next_line(fd);
    while (current_line < map->starting_line && line != NULL)
	{
        free(line);
        current_line++;
        if (current_line < map->starting_line) {
            line = get_next_line(fd);
        }
    }
    while (line != NULL) {
		if (line[0] != '\n')
        	height++;
		line = get_next_line(fd);
		free(line);
    }
    close(fd);
	return (height);	
}

// //	COUNTS ALL THE LINES OF THE CONFIG FILE, NOT JUST THE MAP LINES
// int	search_map_height(t_map *map)
// {
// 	int		height;
// 	int		fd;
// 	char	*line;

// 	height = 0;
// 	fd = 0;
// 	line = NULL;
// 	fd = open(map->file, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (-1);
// 	}
// 	line = get_next_line(fd);
//     while (line != NULL) {
// 		free(line);
//         height++;
// 		line = get_next_line(fd);
//     }
//     close(fd);
// 	return (height);	
// }

// int	search_map_width(char *file)
// {
// 	int width;
// 	int max_width;
// 	int	fd;

// 	width = 0;
// 	max_width = 0;
// 	fd = open(file, O_RDONLY, 0);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (-1);
// 	}

// 	return (width);
// }