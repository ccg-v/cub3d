/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/04 13:31:04 by ccarrace         ###   ########.fr       */
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
	bool		closed;
	size_t		new_x;
	size_t		new_y;
}	t_map;

/* --- Functions ------------------------------------------------------------ */

//	main.c
void	init_map(t_map *map, char *map_file);
int		main(int argc, char **argv);

//	parse.c
int		find_map_starting_line_and_height (t_map *map);
int		find_map_width(t_map *map);
// void	find_map_width(t_map *map, char *line);
char	**allocate_map_array(t_map *map);
int		fill_map_array(t_map *map);
void 	free_map_array(t_map *map);

//	prs_check_map.c
int		check_player(t_map *map);
bool	check_navigability(t_map *map);

//	debug.c
void	print_map_array(t_map *map);

#endif
