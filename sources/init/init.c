/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:02:33 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/25 00:20:55 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, char *map_file)
{
	map->file = map_file;
	map->starting_line = 1;
	map->ending_line = 1;
	map->height = 0;
	map->width = 0;
	map->array = NULL;
	map->i = 0;
	map->j = 0;
	map->visited_height = 0;
	map->visited_width = 0;
	map->visited_array = NULL;
	map->player_x = 0;
	map->player_y = 0;
	map->closed = true;
	map->new_x = 0;
	map->new_y = 0;
}

void  init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->texture_ids[0] = "NO";
	textures->texture_ids[1] = "SO";
	textures->texture_ids[2] = "EA";
	textures->texture_ids[3] = "WE";
	textures->paths_array[0] = &textures->north;
	textures->paths_array[1] = &textures->south;
	textures->paths_array[2] = &textures->east;
	textures->paths_array[3] = &textures->west;	
}

void  init_colors(t_colors *colors)
{
  colors->floor[0] = -1;
  colors->floor[1] = -1;
  colors->floor[2] = -1;
  colors->ceiling[0] = -1; 
  colors->ceiling[1] = -1;
  colors->ceiling[2] = -1;
}