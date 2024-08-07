/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:05:56 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_result	create_arrays(t_data *data)
{
	allocate_map_array(data);
	if (fill_map_array(data) == FAIL)
		return (FAIL);
	allocate_visited(data);
	fill_visited(data);
	return (SUCCESS);
}
