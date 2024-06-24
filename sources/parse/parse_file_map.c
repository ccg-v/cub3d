/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/25 00:51:22 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		find_map_starting_line(t_map *map);
int		find_map_width(t_map *map);
char 	**allocate_map_array(t_map *map);
int 	fill_map_array(t_map *map);
int		is_whitespace(char c);
int		find_map_height(t_map *map);
void	allocate_visited_array(t_map *map);

int	find_map_starting_line(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (((line[0] != ' ' && line[0] != '1') || (line[0] == ' ' && 
		ft_strchr(line, '1') == NULL)) && map->height == 0)
				++map->starting_line;
		else
			break;
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
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
	size_t	len;

	map->i = 0;
	fd = open(map->file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (map->i++ < map->starting_line)
	{
		line = get_next_line(fd);
		if (map->i < map->starting_line)
			free(line);
	}
    while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > map->width)
        	map->width = len;
		free(line);
		line = get_next_line(fd);
    }
	free(line);
	close(fd);
	return (0);
}

char **allocate_map_array(t_map *map)
{
	size_t	i;

	map->array = malloc((map->height) * sizeof(char *));
	if (!map->array)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->array[i] = malloc((map->width + 1) * sizeof(char));
		if (!map->array[i])
			return (NULL);
		i++;
	}
	return (map->array);
}

int fill_map_array(t_map *map)
{
    int     fd;
    char    *line;
    size_t  len;

	fd = open(map->file, O_RDONLY);
    if (fd == -1)
        return (-1);
    map->i = 1;
    line = get_next_line(fd);
    while (map->i < map->starting_line)
    {
        free(line);
        line = get_next_line(fd);
        map->i++;
    }
	map->i = 0;
    while (line && map->i < map->height)
    {
        map->j = 0;
        // Ensure line does not contain a newline at the end
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        // Copy characters to map->array, handling shorter lines
        while (map->j < map->width)
        {
            if (map->j < len && line[map->j] != '\0')
                map->array[map->i][map->j] = line[map->j];
            else
                map->array[map->i][map->j] = '\0';
            map->j++;
        }
		map->array[map->i][map->width] = '\0';
        free(line);
        line = get_next_line(fd);
        map->i++;
    }
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);		
	}	
    free(line);
    close(fd);
    return (0);
}

int	find_map_height(t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	// size_t	current_line;

	fd = open_file(map->file);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	// current_line = 0;
    // while (current_line < map->starting_line && line != NULL)
	// {
    //     current_line++;
    //     if (current_line < map->starting_line)
	// 	{
	// 		free(line);
    //         line = get_next_line(fd);
    //     }
    // }
	read_until_line(fd, &line, map->starting_line);
	while (line && line[0] != '\n')
	{
		i = 0;
		while (is_whitespace(line[i]))
			i++;
		if (line[i] == '1' || line[i] == '0')
			++map->height;
		free(line);
		line = get_next_line(fd);
	}
	// while (line != NULL)
	// {
	// 	free(line);
	// 	line = get_next_line(fd);		
	// }
	read_until_end_of_file(fd, &line);
	free(line);
	close(fd);
	return (0);
}

// void	calculate_map_height_and_cleanup(t_map *map, int fd, char *line)
// {
// 	int i;

// 	while (line && line[0] != '\n')
// 	{
// 		i = 0;
// 		while (is_whitespace(line[i]))
// 			i++;
// 		if (line[i] == '1' || line[i] == '0')
// 			++map->height;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	while (line != NULL)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// }

// void	process_pre_map_lines(t_map *map, int fd, char **line)
// {
// 	size_t current_line = 0;

// 	while (current_line < map->starting_line && *line != NULL)
// 	{
// 		current_line++;
// 		if (current_line < map->starting_line)
// 		{
// 			free(*line);
// 			*line = get_next_line(fd);
// 		}
// 	}
// }

// int	find_map_height(t_map *map)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open_file(map->file);
// 	if (fd < 0)
// 		return (-1);
// 	line = get_next_line(fd);

// 	process_pre_map_lines(map, fd, &line);
// 	calculate_map_height_and_cleanup(map, fd, line);
// 	return (0);
// }


/*	
 *	allocate_visited_array()
 *
 *	Visited_array is initially a copy of the map_array, but expanding
 *	it two rows (one on the top, one on the bottom) and two columns
 *	(one on the left, one on the right). Those columns will be filled
 *	with whitespaces.
 */
void allocate_visited_array(t_map *map)
{
    size_t i;
    size_t j;

	map->visited_array = malloc((map->height + 2) * sizeof(char *));
	if (!map->visited_array)
		return ;
	i = 0;
    while (i < map->height + 2)
	{
        map->visited_array[i] = malloc((map->width + 2) * sizeof(char));
        if (!map->visited_array[i])
		{
            while (i > 0)
                free(map->visited_array[--i]);
            free(map->visited_array);
            return;
        }
        ft_memset(map->visited_array[i], ' ', (map->width + 1));
		map->visited_array[i][map->width + 1] = '\0'; // Set the last character to null-terminator
		i++;
    }
    // Copy the content of the map->array to map->visited_array, ignoring '\0' at the end of each line
    i = 0;
	while (i < map->height)
	{
		j = 0;
        while (j < map->width)
		{
            // Copy each character except the null-terminator
            if (map->array[i][j] != '\0')
                map->visited_array[i + 1][j + 1] = map->array[i][j];
            j++;
        }
		i++;
    }
}

    // // Print the expanded array (REMOVE)
    // for (i = 0; i < map->height + 2; i++) 
	// {
    //     for (j = 0; j < map->width + 1; j++) 
	// 	{
	// 		if (map->visited_array[i][j] == ' ')
	// 			printf(".");
	// 		else
    //         	printf("%c", map->visited_array[i][j]);
    //     }
    //     printf("\n");
    // }

    // // Free the memory allocated for the new array
	// i = 0;
    // while (i < map->height + 2)
	// {
    //     free(map->visited_array[i]);
	// 	i++;
    // }
    // free(map->visited_array);
// }
