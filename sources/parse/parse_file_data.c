/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:28:00 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/12 00:21:06 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void store_rgb_color(const char *line, int *color)
// {
//     int     i;
//     char    **rgb_values;
//     int     values_count;

//     i = -1;
//     values_count = 0;
//     rgb_values = ft_split(line, ',');
//     if (!rgb_values)
//     {
//         printf("Error: Failed to split RGB values.\n");
//         return;
//     }
//     while (rgb_values[values_count] != NULL
//         && ft_strncmp(rgb_values[values_count], "\n", 1)
//         && ft_strncmp(rgb_values[values_count], " ", 1))

//             values_count++;
//     if (values_count == 3)
//     {
//         while (++i < values_count)
//         {
//             color[i] = ft_atoi(rgb_values[i]);
//             if (color[i] < 0 || color[i] > 255)
//             {
//                 printf("Error: Invalid RGB color, parameter out of range\n");
//                 break;
//             } 
//         }
//     }
//     else
//         printf("Error: Invalid RGB color format, must have three parameters\n");
//     while (--values_count >= 0)
//         free(rgb_values[values_count]);
//     free(rgb_values);
// }

int valid_rgb_values(char **rgb_values, int *color)
{
    int i = 0;

    // while (rgb_values[i] != NULL && i < 3)
    while (rgb_values[i] != NULL && ft_strncmp(rgb_values[i], "\n", 1) && i < 3)
    {
        color[i] = ft_atoi(rgb_values[i]);
        if (color[i] < 0 || color[i] > 255)
        {
            printf("Error: Invalid RGB color, parameter out of range\n");
            return (0);  // Invalid
        }
        i++;
    }
    if (rgb_values[i] != NULL)
    {
        printf("Error: Invalid RGB color format, must have three parameters\n");
        return (0);  // Invalid
    }
    return (1);  // Valid
}
void store_rgb_color(const char *line, int *color)
{
    char    **rgb_values;
	int		i;

    rgb_values = ft_split(line, ',');
    if (!rgb_values)
    {
        printf("Error: Failed to split RGB values.\n");
        return;
    }
    if(!valid_rgb_values(rgb_values, color))
    {
        i = 0;
        while (rgb_values[i] != NULL)
        {
            free(rgb_values[i]);
            i++;
        }
        free(rgb_values);
        return;
    }
    i = 0;
    while (rgb_values[i] != NULL)
    {
        free(rgb_values[i]);
        i++;
    }
    free(rgb_values);
}


int check_colors(int *color_found)
{
    if (color_found == 0)
    {
        printf("Error: No colors defined in the file\n");
        return (-1);
    }
    else if (*color_found == 1)
    {
        printf("Error: Color for the ceiling is missing in the file\n");
        return (-1);
    }
    else if (*color_found == 2)
    {
        printf("Error: Color for the floor is missing in the file\n");
        return (-1);
    }
    else if (*color_found == 3)
    {
        printf("Colors ok!\n");
        return (0);
    }
    // else if (*color_found > 3)
	else
        printf("Error: Too many colors defined in the file\n");
    return (-1);
}

void process_color_line(t_colors *colors, const char *line, int *colors_found)
{
    char	surface;

	surface = *line;
	line++;
	while (*line == ' ' && *line != '\n')
		line++;
	if (surface == 'F')
	{
		store_rgb_color(line, colors->floor);
		*colors_found += 1;
	}
	else if (surface == 'C')
	{
		store_rgb_color(line, colors->ceiling);
		*colors_found += 2;
	}
}

int parse_colors(t_map *map, t_colors *colors)
{
    int 	fd;
    char	*line;
    char	*original_line;
	int		colors_found;	

    fd = open_file(map->file);
	colors_found = 0;
    if (fd == -1)
        return (-1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        original_line = line;  // Store the original pointer for freeing later
        if (*line == 'F' || *line == 'C')
            process_color_line(colors, line, &colors_found);
        free(original_line);  // Free the original pointer
        line = get_next_line(fd);
    }
    close(fd);
	check_colors(&colors_found);
    return (0);
}


// int parse_colors(t_map *map, t_colors *colors)
// {
//     int     fd;
//     char    *line;
//     int     colors_found;
//     char    *original_line;

//     fd = open_file(map->file);
//     if (fd == -1)
//         return (-1);
//     colors_found = 0;
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         original_line = line;  // Store the original pointer for freeing later
//         if (*line == 'F')
//         {
//             line++;
//             while (*line == ' ' && *line != '\n')
//                 line++;
//             store_rgb_color(line, colors->floor);
//             colors_found += 1;
//         }
//         else if (*line == 'C')
//         {
//             line++;
//             while (*line == ' ' && *line != '\n')
//                 line++;
//             store_rgb_color(line, colors->ceiling);
//             colors_found += 2;
//         }
//         free(original_line);  // Free the original pointer
//         line = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }

