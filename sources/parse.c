/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/01 19:53:35 by ccarrace         ###   ########.fr       */
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

void free_map_array(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		// printf("freeing map->array[%zu] = '%s'\n", i, map->array[i]);
		free(map->array[i]);
		i++;
	}

	free(map->array);
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
			if (line[0] != '\n') // ignore newlines after map
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
		map->array[i] = malloc((map->width) * sizeof(char));
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

    fd = open_file(map->file);
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
    while (map->i < map->height)
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
                map->array[map->i][map->j] = '\0';  // Fill remaining with spaces or another default character
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
