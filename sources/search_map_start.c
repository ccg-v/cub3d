/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/29 00:49:30 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while index < len(lines):
//     if lines[index] starts with "NO" or "SO" or "WE" or "EA" or "F" or "C":
//         process_texture_or_color(lines[index])
//     elif lines[index] contains only whitespace:
//         # Skip the line
//         index += 1
//     else:
//         break
//     index += 1

#include "cub3d.h"

int	count_lines(char *file)
{
	int		fd;
	char	*line;
	int		num_lines;

	fd = open(file, O_RDONLY, 0);
	line = "";
	num_lines = 0;

	while (line != NULL)
	{
		line = get_next_line(fd);
		num_lines++;
		free(line);
	}
	// free(line);
	close(fd);
	return (num_lines);
}
//	// 	(MINE): WORKS BUT TOO LONG!
// int set_map_starting_line(char *file)
// {
//     int fd;
//     char *line;
//     int map_starting_line;

//     fd = open(file, O_RDONLY, 0);
//     if (fd == -1) {
//         perror("Error opening file");
//         return (-1);
//     }
//     line = get_next_line(fd);
//     map_starting_line = 0;
//     while (line != NULL)
//     {
//         map_starting_line++;
// 		if (line[0] == ' ')
// 		{
// 			int i = 0;
// 			while (line[i] != '\n')
// 			{
// 				if (line[i] == '1')
// 				{
// 					close(fd);
// 					free(line);
// 					return (map_starting_line);
// 				}
// 				i++;
// 			}
// 		}
//         if ((line[0] == '1' && line[0] != '\n'))
//             break;
//         free(line);
//         line = get_next_line(fd);
//     }
// 	free(line);
//     close(fd);
//     return (map_starting_line);
// }

//	(GEMINI): WORKS BUT OUT OF NORM
// int set_map_starting_line(char *file)
// {
//     int fd;
//     char *line;
//     int map_starting_line = 0;

//     fd = open(file, O_RDONLY, 0);
//     if (fd == -1) {
//         perror("Error opening file");
//         return (-1);
//     }
//     while ((line = get_next_line(fd)) != NULL) {
//         map_starting_line++;
//         if (line[0] == ' ' && ft_strchr(line, '1') != NULL)
// 		{
//             free(line);
//             close(fd);
//             return map_starting_line;
//         }
//         if (line[0] == '1')
//             break;
//         free(line);
//     }
//     free(line);
//     close(fd);
//     return (map_starting_line);
// }

int	set_map_starting_line(char *file)
{
	int		fd;
	char	*line;
	int		map_starting_line;

	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	map_starting_line = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map_starting_line++;
		if (line[0] == ' ' && ft_strchr(line, '1') != NULL)
		{
			free(line);
			close(fd);
			return (map_starting_line);
		}
		if (line[0] == '1')
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (map_starting_line);
}
