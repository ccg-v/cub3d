/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/25 14:09:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static result	find_map_starting_line(t_map *map)
{
	int		fd;
	char	*line;

	fd = open_file(map->file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (((line[0] != ' ' && line[0] != '1') || (line[0] == ' '
			&& ft_strchr(line, '1') == NULL)) && map->height == 0)
			++map->starting_line;
		else
			break ;
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
	return (SUCCESS);
}

static result	find_map_height(t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_file(map->file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
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
	read_until_end_of_file(fd, &line);
	free(line);
	close(fd);
	return (SUCCESS);
}

static result	find_map_width(t_map *map)
{
	int		fd;
	char	*line;
	size_t	len;

	map->i = 0;
	fd = open_file(map->file);
	if (fd < 0)
		return (FAIL);
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
	return (SUCCESS);
}

result	find_map_dimensions(t_map *map)
{
	if (find_map_starting_line(map) == FAIL
		|| find_map_width(map) == FAIL
		|| find_map_height(map) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
