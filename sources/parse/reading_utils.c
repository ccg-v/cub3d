/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:55:28 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/23 22:38:00 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
 *	These are just snippets of code to shorten the functions that open and read
 *	a file and need to move to specific lines or sections
 */

#include "cub3d.h"

int open_file(const char *file_path)
{
    int fd;
	
	fd = open(file_path, O_RDONLY);
    if (fd < 0)
        printf("Error: '%s': Could not open the file\n", file_path);
    return fd;
}


void read_until_line(int fd, char **line, int endline_index)
{
    int i;
	
	i = 0;
    while (i < endline_index)
    {
        free(*line);
        *line = get_next_line(fd);
        i++;
    }
}

void read_until_end_of_file(int fd, char **line)
{
    while (*line != NULL)
    {
        free(*line);
        *line = get_next_line(fd);
    }
}
