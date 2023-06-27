/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:06:28 by jdagoy            #+#    #+#             */
/*   Updated: 2023/06/27 15:13:28 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	print_str(t_fdf *fdf, int x, int y, char *str)
{
	mlx_string_put(fdf->mlx, fdf->win, x, y, 0xFFFFFF, str);
}

static void	draw_mapinfo(t_fdf *fdf)
{
	print_str(fdf, 1600, 20, "MAP INFO");
}

static void	draw_rectangle(t_fdf *fdf, t_point *boundaries)
{
	float	i;
	float	thickness;

	i = 0.0;
	thickness = 5.0;
	while (i < thickness)
	{
		draw_line_dda(fdf, boundaries[0], boundaries[1]);
		draw_line_dda(fdf, boundaries[1], boundaries[2]);
		draw_line_dda(fdf, boundaries[2], boundaries[3]);
		draw_line_dda(fdf, boundaries[3], boundaries[0]);
		boundaries[0].axis[X_AXIS] -= 0.5;
		boundaries[0].axis[Y_AXIS] -= 0.5;
		boundaries[1].axis[X_AXIS] -= 0.5;
		boundaries[1].axis[Y_AXIS] -= 0.5;
		boundaries[2].axis[X_AXIS] -= 0.5;
		boundaries[2].axis[Y_AXIS] -= 0.5;
		boundaries[3].axis[X_AXIS] -= 0.5;
		boundaries[3].axis[Y_AXIS] -= 0.5;
		i += 0.5;
	}
}


static void	render_menu_box(t_fdf *fdf)
{
	t_point	boundaries[4];
	int		menu_x;
	int		menu_y;

	menu_x = WINDOW_WIDTH - MENU_WIDTH - 50;
	menu_y = WINDOW_HEIGHT - MENU_HEIGHT - 50;
	boundaries[0].axis[X_AXIS] = menu_x;
	boundaries[0].axis[Y_AXIS] = menu_y;
	boundaries[0].color = 0xFFFFFF;
	boundaries[1].axis[X_AXIS] = menu_x;
	boundaries[1].axis[Y_AXIS] = menu_y + MENU_HEIGHT;
	boundaries[1].color = 0xFFFFFF;
	boundaries[2].axis[X_AXIS] = menu_x + MENU_WIDTH;
	boundaries[2].axis[Y_AXIS] = menu_y + MENU_HEIGHT;
	boundaries[2].color = 0xFFFFFF;
	boundaries[3].axis[X_AXIS] = menu_x + MENU_WIDTH;
	boundaries[3].axis[Y_AXIS] = menu_y;
	boundaries[3].color = 0xFFFFFF;
	draw_rectangle(fdf, boundaries);
}


void	draw_menu(t_fdf *fdf)
{
	draw_mapinfo(fdf);
	render_menu_box(fdf);
}
