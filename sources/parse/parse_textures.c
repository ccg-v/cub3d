/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:44 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/11 21:55:40 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_textures(t_map *map, t_textures *textures)
{
    int fd;
    char *line;

	fd = open_file(map->file);
	if (fd == -1)
		return (-1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            textures->north = ft_strdup(line + 3);
        else if (ft_strncmp(line, "SO ", 3) == 0)
            textures->south = ft_strdup(line + 3);
        else if (ft_strncmp(line, "WE ", 3) == 0)
            textures->west = ft_strdup(line + 3);
        else if (ft_strncmp(line, "EA ", 3) == 0)
            textures->east = ft_strdup(line + 3);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}

int check_textures(t_textures *textures)
{
    if (textures->north != NULL && textures->south != NULL
        && textures->east != NULL && textures->west != NULL)
    {
        printf("Textures ok!\n");
        return (0);
    }
    if (textures->north == NULL && textures->south == NULL
        && textures->east == NULL && textures->west == NULL)
    {
        printf("Error: no textures defined in the file\n");
        return (-1);
    }    
    if (textures->north == NULL)
        printf("Error: texture NO is missing in the file\n");
    if (textures->south == NULL)
        printf("Error: texture SO is missing in the file\n");
    if (textures->east == NULL)
        printf("Error: texture EA is missing in the file\n");
    if (textures->west == NULL)
        printf("Error: texture WE is missing in the file\n");
    return (-1);
}
