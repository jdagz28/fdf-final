/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:13:02 by jdagoy            #+#    #+#             */
/*   Updated: 2023/06/28 22:39:13 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_z(t_map_data *map, int index)
{
	if (map->limits.axis[Z_AXIS] < map->points[index].axis[Z_AXIS])
		map->limits.axis[Z_AXIS] = map->points[index].axis[Z_AXIS];
	if (map->z_min > map->points[index].axis[Z_AXIS])
		map->z_min = map->points[index].axis[Z_AXIS];
}

int	valid_point(char *value)
{
	int	valid;

	valid = 0;
	if (*value == '-' || *value == '+' || ft_isdigit(*value))
		valid++;
	value++;
	while (ft_isdigit(*value))
	{
		value++;
		valid++;
	}
	if (valid == 0)
		return (0);
	else
		return (1);
}

int	check_hexcolor(char *line, int *error)
{
	char	**color;
	int		get_color;

	if (ft_strchr(line, ',') != 0)
	{
		color = ft_split(line, ',');
		if (!color)
		{
			*error = 1;
			return (0);
		}
		get_color = strtol(color[1] + 2, NULL, 16);
		free_split(color);
		return (get_color);
	}
	else
		return (0);
}

static void	get_mapsize_cont(t_map_data *map, int elem_count)
{
	if (elem_count > 0 && (map->limits.axis[X_AXIS] != elem_count))
		exit_error("Map row elements are different.\n");
	map->limits.axis[Y_AXIS] = map->limits.axis[Y_AXIS] + 1;
	map->map_height = map->limits.axis[Y_AXIS];
	map->map_width = map->limits.axis[X_AXIS];
	map->dimension = map->map_height * map->map_width;
}

void	get_mapsize(t_map_data *map)
{
	int	i;
	int	elem_count;

	i = -1;
	elem_count = 0;
	while (map->mapread[++i])
	{
		if (map->mapread[i] == '\n' && map->mapread[i + 1] == '\0')
			break ;
		if (ft_isalnum(map->mapread[i]) && (map->mapread[i + 1] == ' ' \
				|| map->mapread[i + 1] == '\n' || map->mapread[i + 1] == '\0'))
				elem_count++;
		if (map->mapread[i] == '\n')
		{
			map->limits.axis[Y_AXIS] = map->limits.axis[Y_AXIS] + 1;
			if (map->limits.axis[X_AXIS] != 0 && \
					(map->limits.axis[X_AXIS] != elem_count))
				exit_error("Map row elements are different.\n");
			else
				map->limits.axis[X_AXIS] = elem_count;
			elem_count = 0;
		}
	}
	get_mapsize_cont(map, elem_count);
}
