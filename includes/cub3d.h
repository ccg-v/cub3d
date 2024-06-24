/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/24 13:21:09 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

// /* --- Define preprocessor directives ------------------------------------ */

// #define SUCCESS 1
// #define FAIL 0

/* --- Enum definitions ----------------------------------------------------- */

typedef enum 
{
    FAIL = 0,
    SUCCESS = 1
} result;

typedef enum
{
	FALSE = 0,
	TRUE = 1
} boolean;

/* --- ANSI escape codes ---------------------------------------------------- */

# define BOLD_BRIGHT_GREEN "\033[1;92m"
# define BOLD_BRIGHT_RED "\033[1;91m"
# define BACKGROUND_BRIGHT_RED "\033[0;101m"
# define RESET "\x1B[0m"   // resets all terminal attributes to default settings

/* --- Data structures ------------------------------------------------------ */

typedef struct s_map
{
	char		*file;
	size_t		starting_line;
	size_t		ending_line;
	size_t		width;
	size_t		height;
	char		**array;
	size_t		i;
	size_t		j;
	char		**visited_array;
	size_t		player_x;
	size_t		player_y;
	char		player_orientation;
	bool		closed;
	size_t		new_x;
	size_t		new_y;
}	t_map;

typedef struct s_textures
{
	char	*north;
    char	*south;
    char	*west;
    char	*east;
	char	**paths_array[4];
	char	*texture_ids[4];
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

/* --- Init ----------------------------------------------------------------- */

//	init.c
void	init_map(t_map *map, char *map_file);
void  	init_textures(t_textures *textures);
void  	init_colors(t_colors *colors);

/* --- Parse ---------------------------------------------------------------- */

//	check_file
boolean is_directory(char *str);
boolean can_open_file(char *str);
result	file_check(char *file_name);

//	check_scene_description
result	check_scene_description(t_map *map);

//	check_textures.c
result	check_textures(t_map *map, t_textures *textures);

//	check_colors.c
result	check_colors(t_map *map, t_colors *colors);

//	check_player.c
int		check_player(t_map *map);
int 	all_chars_are_valid(t_map *map);
bool	check_navigability(t_map *map);

//	check_walls.c
void	print_visited_map(t_map *map);
void	dfs(t_map *map, int row, int column);
int		is_map_closed(t_map *map);
int		is_fully_walkable(t_map *map);

//	parse_file_map.c
int		find_map_starting_line(t_map *map);
int		find_map_height(t_map *map);
int		find_map_width(t_map *map);
char	**allocate_map_array(t_map *map);
int		fill_map_array(t_map *map);
void	allocate_visited_array(t_map *map);

//	parse_utils.c
int		is_file_type_valid(char *filename, char *expected_extension);
void 	free_array(char **array, size_t height);
void	free_rgb_values(char **rgb_array);
int 	is_valid_number(const char *str);
size_t	find_file_length(char *file);

//	parse_utils2.c
int		is_whitespace(char c);
void	trim_and_reduce_spaces(char *line);
//	reading_utils.c
int 	open_file(const char *file_path);
void	read_until_line(int fd, char **line, int endline_index);
void	read_until_end_of_file(int fd, char **line);

/* --- Debug ------------------------------------------------------- */

//	debug.c
void	print_map_array(t_map *map);

#endif
