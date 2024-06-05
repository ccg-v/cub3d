/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_check_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/06 00:51:47 by ccarrace         ###   ########.fr       */
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
        printf("Error: no configuration found in file");
    return (0);
}