/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:07:08 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/11 19:48:15 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_colors(t_map *map, t_colors *colors)
{
    int     fd;
    char    *line;
    int     colors_found;
    char    *original_line;

    fd = open_file(map->file);
    if (fd == -1)
        return (-1);
    colors_found = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        original_line = line;  // Store the original pointer for freeing later
        if (*line == 'F')
        {
            line++;
            while (*line == ' ' && *line != '\n')
                line++;
            store_rgb_color(line, colors->floor);
            colors_found += 1;
        }
        else if (*line == 'C')
        {
            line++;
            while (*line == ' ' && *line != '\n')
                line++;
            store_rgb_color(line, colors->ceiling);
            colors_found += 2;
        }
        free(original_line);  // Free the original pointer
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}

int valid_color_lines(t_map *map, t_colors *colors)
{
    int fd;
    char *line;
    int colors_found;
    char *original_line;

    fd = open_file(map->file);
    if (fd == -1)
        return (-1);
    colors_found = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        original_line = line;  // Store the original pointer for freeing later
        if (*line == 'F' || *line == 'C')
        {
            line++;
            while (*line == ' ' && *line != '\n')
                line++;
            if (*original_line == 'F')
            {
                store_rgb_color(line, colors->floor);
                colors_found += 1;
            }
            else if (*original_line == 'C')
            {
                store_rgb_color(line, colors->ceiling);
                colors_found += 2;
            }
        }
        free(original_line);  // Free the original pointer
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}

