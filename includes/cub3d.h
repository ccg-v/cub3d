/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/11 22:52:03 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "libft.h"

/* --- Data structures ------------------------------------------------------ */

typedef struct s_map
{
	char		*file;
	size_t		starting_line;
	size_t		width;
	size_t		height;
	char		**array;
	size_t		i;
	size_t		j;
	char		**visited;
	size_t		player_x;
	size_t		player_y;
	char		player_orientation;
	bool		closed;
	size_t		new_x;
	size_t		new_y;
}	t_map;

typedef struct s_textures
{
	char *north;
    char *south;
    char *west;
    char *east;
}	t_textures;

typedef struct s_colors
{
    int floor[3];
    int ceiling[3];
}	t_colors;


/* === Functions ============================================================ */

//	main.c
void	init_map(t_map *map, char *map_file);
int		main(int argc, char **argv);

/* --- Parse ------------------------------------------------------- */

//	check_file_data.c
int 	check_configuration_data(t_map *map);

//	check_player.c
int		check_player(t_map *map);
int 	all_chars_are_valid(t_map *map);
bool	check_navigability(t_map *map);

//	parse_file_data.c
// int 	parse_textures(t_map *map, t_textures *textures);
// int 	check_textures(t_textures *textures);
int		parse_colors(t_map *map, t_colors *colors);
// int 	check_colors(t_colors *colors);
// int 	check_colors(int color_found);

//	parse_file_map.c
int		find_map_starting_line_and_height (t_map *map);
int		find_map_width(t_map *map);
char	**allocate_map_array(t_map *map);
int		fill_map_array(t_map *map);

//	parse_utils.c
int 	open_file(const char *file);
void 	free_map_array(t_map *map);

/* --- Debug ------------------------------------------------------- */

//	debug.c
void	print_map_array(t_map *map);

#endif
