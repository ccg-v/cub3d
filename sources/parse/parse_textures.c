/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:44 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/14 23:40:38 by ccarrace         ###   ########.fr       */
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

void	trim_last_char(char *path)
{
	int		len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
}

// int parse_textures(t_map *map, t_textures *textures)
// {
//     int fd;
//     char *line;
// 	char *trimmed_path;

//     fd = open(map->file, O_RDONLY);
//     if (fd < 0)
// 	{
// 		printf("Failed opening file\n");
//         return (-1);
// 	}
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
// 		map->i = 0;
//         while (map->i < 4)
//         {
//             if (ft_strncmp(line, textures->texture_ids[map->i], 2) == 0)
//             {
//                 if (*(textures->paths_array[map->i]) != NULL)
//                 {
//                     printf("Error: Two %s textures in the file\n", textures->texture_ids[map->i]);
//                     free(line);
//                     close(fd);
//                     return (-1);
//                 }
// 				int k = 2;
// 				while (line[k] == ' ')
// 					k++;
// 				trimmed_path = ft_strdup(line + k);
//                 trim_last_char(trimmed_path);
// 				*(textures->paths_array[map->i]) = trimmed_path;
//                 break;
//             }
// 			map->i++;
//         }
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }

int store_texture_path(char *line, t_textures *textures)
{
    int i = 0;
    int k;
    char *trimmed_path;

    while (i < 4)
    {
        if (ft_strncmp(line, textures->texture_ids[i], 2) == 0)
        {
            if (*(textures->paths_array[i]) != NULL)
            {
                printf("Error: Two %s textures in the file\n", textures->texture_ids[i]);
                return (-1);
            }
            k = 2;
            while (line[k] == ' ')
                k++;
            trimmed_path = ft_strdup(line + k);
            trim_last_char(trimmed_path);
            *(textures->paths_array[i]) = trimmed_path;
            break;
        }
        i++;
    }
    return (0);
}

int parse_textures(t_map *map, t_textures *textures)
{
    int fd;
    char *line;

    fd = open(map->file, O_RDONLY);
    if (fd < 0)
    {
        printf("Failed opening file\n");
        return (-1);
    }

    line = get_next_line(fd);
    while (line != NULL)
    {
        if (store_texture_path(line, textures) == -1)
        {
            free(line);
            close(fd);
            return (-1);
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}



int check_textures_in_file(t_textures *textures)
{
    if (textures->north != NULL && textures->south != NULL
        && textures->east != NULL && textures->west != NULL)
    // {
        // printf("Textures ok!\n");
        return (0);
    // }
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

int check_textures_path(t_textures *textures)
{
	int i;
	int fd;
	char *path;
	
	i = 0;
	while (i < 4)
	{
    	path = *(textures->paths_array[i]);
    	fd = open(path, O_DIRECTORY);
    	if (fd >= 0)
		{
      		printf("Error: '%s' is a directory\n", path);
      		return (-1);  // Early exit on error
    	}
    	fd = open(path, O_RDONLY);
    	if (fd < 0)
		{
      	printf("Error: Cannot open %s\n", path);
      	return (-1);  // Early exit on error
    	}
    	close(fd);
    	i++;
  	}
	printf("Texture paths ok!\n");
	return (0);
}

// int check_is_dir(t_textures *textures)
// {
//     int i;
//     int fd;
//     char *path;

//     i = 0;
//     while (i < 4)
//     {
//         path = *(textures->paths_array[i]);
//         fd = open(path, O_DIRECTORY);
//         if (fd < 0)
// 		{
//             printf("Error: %s is a directory, not a file\n", path);
// 			return (-1);
// 		}
// 		printf("%s is a file\n", path);
// 		close(fd);
//         i++;
//     }
//     return (0);
// }

// int check_textures_path(t_textures *textures)
// {
//     int i;
//     int fd;
//     char *path;

// 	if (check_is_dir(textures) == -1)
// 		return (-1);
//     i = 0;
//     while (i < 4)
//     {
//         path = *(textures->paths_array[i]);
//         fd = open(path, O_RDONLY);
//         if (fd < 0)
// 		{
//             printf("Cannot open %s\n", path);
// 			return (-1);
// 		}
// 		printf("%s opened\n", path);
// 		close(fd);
//         i++;
//     }
//     return (0);
// }


