/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/16 00:33:55 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    free(line);
    close(fd);
    return (0);
}

// ' ' space, '\t' horizontal tab, '\r' return carriage
// '\v' vertical tab, '\f' form feed
int	is_whitespace(char c)
{
	if (c == ' ' ||
		c == '\t' ||
		c == '\r' ||
		c == '\v' ||
		c == '\f') 
		return (1);
	return (0);
}

int	find_map_height(t_map *map)
{
	int		fd;
	size_t 	current_line;
	char	*line;
	int		i;

	fd = open(map->file, O_RDONLY);
	if (fd == -1)
		return (-1);
	current_line = 0;
	line = get_next_line(fd);
    while (current_line < map->starting_line && line != NULL)
	{
        current_line++;
        if (current_line < map->starting_line)
		{
			free(line);
            line = get_next_line(fd);
        }
    }
	while (line[0] != '\n')
	{
		i = 0;
		while (is_whitespace(line[i]))
			i++;
		if (line[i] == '1')
			map->height++;
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
