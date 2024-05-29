/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/29 21:28:25 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

/* --- Data structures ------------------------------------------------------ */

typedef struct s_map
{
	char	*file;
	int		starting_line;
	int		width;
	int		height;
}	t_map;

/* --- Functions ------------------------------------------------------------ */

void	init_map(t_map *map, char *map_file);
int		main(int argc, char **argv);

int		search_map_starting_line (t_map *map);
int		search_map_height(t_map *map);

#endif
