/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:33:05 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/23 20:15:29 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

boolean is_directory(char *str)
{
    int fd;

	fd = open(str, O_DIRECTORY);
	if (fd < 0)
		return (FALSE);
	printf("Error: %s is a directory, not a file\n", str);
	close(fd);
    return (TRUE);
}

boolean can_open_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: '%s': Could not open the file\n", str);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

result	file_check(char *file_name)
{
	if (is_directory(file_name) == TRUE)
		return (FAIL);
	if (can_open_file(file_name)== FALSE)
		return (FAIL);
	if (!is_file_type_valid(file_name, ".cub"))
	{
		printf("Error: Wrong file type (must be .cub)\n");
		return (FAIL);
	}
	return (SUCCESS);
}