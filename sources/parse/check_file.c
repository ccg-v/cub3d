/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:33:05 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/23 12:47:05 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

result check_is_dir(char *str)
{
    int fd;

	fd = open(str, O_DIRECTORY);
	if (fd < 0)
	{
		// printf("%s is a file\n", str);
		return (FAIL);
	}
	printf("Error: %s is a directory, not a file\n", str);
	close(fd);
    return (SUCCESS);
}

result	file_check(char *file_name)
{
	if (check_is_dir(file_name) == SUCCESS)
		return (FAIL);
	if (!file_type_is_valid(file_name, ".cub"))
	{
		printf("Error: Wrong file type (must be .cub)\n");
		return (FAIL);
	}
	return (SUCCESS);
}