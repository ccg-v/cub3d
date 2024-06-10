/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:28:00 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/10 23:25:29 by ccarrace         ###   ########.fr       */
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

void store_rgb_color(char *line, int *color)
{
    int     i;
    char    **rgb_values;
    int     values_count;

    i = -1;
    values_count = 0;
    rgb_values = ft_split(line, ',');
    if (!rgb_values)
    {
        printf("Error: Failed to split RGB values.\n");
        return;
    }
    while (rgb_values[values_count] != NULL
        && ft_strncmp(rgb_values[values_count], "\n", 1)
        && ft_strncmp(rgb_values[values_count], " ", 1))

            values_count++;
    if (values_count == 3)
    {
        while (++i < values_count)
        {
            color[i] = ft_atoi(rgb_values[i]);
            if (color[i] < 0 || color[i] > 255)
            {
                printf("Error: Invalid RGB color code\n");
                break;
            } 
        }
    }
    else
        printf("Error: Incomplete RGB color code\n");
    while (--values_count >= 0)
        free(rgb_values[values_count]);
    free(rgb_values);
}

int check_colors(int color_found)
{
    if (color_found == 0)
    {
        printf("Error: no colors defined in the file\n");
        return (-1);
    }
    else if (color_found == 1)
    {
        printf("Error: color for the ceiling is missing in the file\n");
        return (-1);
    }
    else if (color_found == 2)
    {
        printf("Error: color for the floor is missing in the file\n");
        return (-1);
    }
    else if (color_found == 3)
    {
        printf("Colors Ok!\n");
        return (0);
    }
    else
        printf("Error: Too many colors defined in the file\n");
    return (-1);
}

int parse_colors(t_map *map, t_colors *colors)
{
    int     fd;
    char    *line;
    int     color_found;

	fd = open_file(map->file);
	if (fd == -1)
		return (-1);
    color_found = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (ft_strncmp(line, "F ", 2) == 0)
        {
            store_rgb_color(line + 2, colors->floor);
            color_found += 1;
        }
        else if (ft_strncmp(line, "C ", 2) == 0)
        {
            store_rgb_color(line + 2, colors->ceiling);
            color_found += 2;
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    check_colors(color_found);
    return (0);
}

// int check_colors(t_colors *colors)
// {
//     if (!colors->ceiling != NULL && colors->floor != NULL)
//     {
//         printf("Colors ok!\n");
//         return (0);
//     }
//     if (colors->ceiling == NULL && colors->floor == NULL)
//     {
//         printf("Error: no colors defined in the file");
//         return (-1);
//     }
//     if (colors->floor == NULL)
//         c
//     if (colors->ceiling == NULL)
//         printf("Error: color for the ceiling is missing in the file\n");
//     return (-1);  
// }
