/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:43:07 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/08 01:00:15 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb_to_hex(int *rgb_array)
{
	return (((rgb_array[0] & 0xFF) << 16)
		| ((rgb_array[1] & 0xFF) << 8)
		| (rgb_array[2] & 0xFF));
}

int	find_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	display_map_error(char *str, int code)
{
	printf(RED " \u2718 " RESET);
	printf("Error\n%s\n", str);
	if (code)
		printf(RED "File is not valid\n" RESET);
}
