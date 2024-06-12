/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:44 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/12 22:46:53 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int parse_textures(t_map *map, t_textures *textures)
// {
//     int		fd;
//     char	*line;

// 	fd = open_file(map->file);
// 	if (fd == -1)
// 		return (-1);
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         if (ft_strncmp(line, "NO", 2) == 0)
// 		{
// 			if (textures->north != NULL)
// 			{
// 				printf("Error: two NO textures in the file\n");
// 				return (-1);
// 			}
//             textures->north = ft_strdup(line + 2);
// 		}
//         else if (ft_strncmp(line, "SO", 2) == 0)
// 		{
// 			if (textures->south != NULL)
// 			{
// 				printf("Error: two SO textures in the file\n");
// 				return (-1);
// 			}
//             textures->south = ft_strdup(line + 2);
// 		}
//         else if (ft_strncmp(line, "WE ", 2) == 0)
// 		{
// 			if (textures->west != NULL)
// 			{
// 				printf("Error: two WE textures in the file\n");
// 				return (-1);
// 			}
//             textures->west = ft_strdup(line + 2);
// 		}
//         else if (ft_strncmp(line, "EA ", 2) == 0)
// 		{
// 			if (textures->east != NULL)
// 			{
// 				printf("Error: two EA textures in the file\n");
// 				return (-1);
// 			}
//             textures->east = ft_strdup(line + 2);
// 		}
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }

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
		map->i = 0;
        while (map->i < 4)
        {
            if (ft_strncmp(line, textures->texture_ids[map->i], 2) == 0)
            {
                if (*(textures->texture_array[map->i]) != NULL)
                {
                    printf("Error: two %s textures in the file\n", textures->texture_ids[map->i]);
                    free(line);
                    close(fd);
                    return (-1);
                }
                *(textures->texture_array[map->i]) = ft_strdup(line + 2);
                break;
            }
			map->i++;
        }
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
