/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/28 20:52:48 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

/* --- Data structures ------------------------------------------------------ */

typedef struct s_map
{
	char	*map_file;
	int		width;
	int		height;
}	t_map;

/* --- Functions ------------------------------------------------------------ */

int		main(int argc, char **argv);
// void	get_map_dim(char *file_name);
int		count_lines(char *file);
int		set_map_starting_line (char *file);

#endif
