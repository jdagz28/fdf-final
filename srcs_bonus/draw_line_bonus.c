/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:09:04 by jdagoy            #+#    #+#             */
/*   Updated: 2023/06/28 22:49:33 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	pixel_in_window(t_point pixel)
{
	if (pixel.axis[X_AXIS] < 0 || pixel.axis[X_AXIS] > WINDOW_WIDTH)
		return (0);
	if (pixel.axis[Y_AXIS] < 0 || pixel.axis[Y_AXIS] > WINDOW_HEIGHT)
		return (0);
	return (1);
}

static float	do_sqrt(t_point start, t_point end)
{
	float	res;

	res = sqrt(((end.axis[X_AXIS] - start.axis[X_AXIS]) * (end.axis[X_AXIS] \
		- start.axis[X_AXIS])) + ((end.axis[Y_AXIS] - start.axis[Y_AXIS]) \
		* (end.axis[Y_AXIS] - start.axis[Y_AXIS])));
	return (res);
}

void	draw_line_dda(t_fdf *fdf, t_point start, t_point end)
{
	int		steps;
	t_point	pixel;
	float	indices[2];
	int		len;
	int		pixels;

	if (fabsf(end.axis[X_AXIS] - start.axis[X_AXIS]) \
			> fabsf(end.axis[Y_AXIS] - start.axis[Y_AXIS]))
		steps = fabsf(end.axis[X_AXIS] - start.axis[X_AXIS]);
	else
		steps = fabsf(end.axis[Y_AXIS] - start.axis[Y_AXIS]);
	indices[X_AXIS] = (end.axis[X_AXIS] - start.axis[X_AXIS]) / (float)steps;
	indices[Y_AXIS] = (end.axis[Y_AXIS] - start.axis[Y_AXIS]) / (float)steps;
	pixel.axis[X_AXIS] = start.axis[X_AXIS];
	pixel.axis[Y_AXIS] = start.axis[Y_AXIS];
	pixels = do_sqrt(start, end);
	len = pixels;
	while (steps--)
	{
		pixel.color = gradient(start.color, end.color, len, len - steps);
		my_mlx_pixel_put(fdf, pixel);
		pixel.axis[X_AXIS] += indices[X_AXIS];
		pixel.axis[Y_AXIS] += indices[Y_AXIS];
	}
}

static void	connect_points(t_point *point, t_fdf *fdf, int density, int line)
{
	int	i;
	int	x_end;
	int	y_end;

	i = 0;
	while (i < (int)fdf->map.limits.axis[X_AXIS])
	{
		x_end = i + density;
		if (x_end >= (int)fdf->map.limits.axis[X_AXIS])
			x_end = (int)fdf->map.limits.axis[X_AXIS] - 1;
		y_end = i + (int)fdf->map.limits.axis[X_AXIS] * density;
		if (point[i].ispoint)
		{
			draw_line_dda(fdf, point[i], point[x_end]);
			if (line + density < (int)fdf->map.limits.axis[Y_AXIS])
				draw_line_dda(fdf, point[i], point[y_end]);
		}
		i += density;
	}
}

void	draw_wireframe(t_fdf *fdf, t_point *point)
{
	int	i;
	int	density;

	density = 8 / fdf->map.scale;
	if (density == 0)
		density = 1;
	i = 0;
	while (i < fdf->map.dimension)
	{
		connect_points(&point[i], fdf, \
						density, i / fdf->map.limits.axis[X_AXIS]);
		i = i + fdf->map.limits.axis[X_AXIS] * density;
	}
}
