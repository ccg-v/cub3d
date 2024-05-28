/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/29 00:11:47 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%s file has %d lines\n", argv[1], count_lines(argv[1]));
	printf("map starting line is %d\n", set_map_starting_line (argv[1]));
	return (0);
}