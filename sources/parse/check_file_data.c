/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/12 23:42:45 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int no_configuration(t_map *map)
{
    if (map->starting_line == 1)
        return (1);
    return (0);
}

int check_configuration_data(t_map *map)
{
    if (no_configuration(map))
        printf("Error: File contains only map\n");
    return (0);
}

int	file_type_is_valid(char *filename, char *expected_extension)
{
	size_t	len;
	char	*file_extension;

	len = ft_strlen(filename);
	file_extension = ft_substr(filename, len - 4, 4);
	if (ft_strncmp(file_extension, expected_extension, 4) != 0)
	{
		free(file_extension);
		return (0);
	}
	free(file_extension);
	return (1);
}