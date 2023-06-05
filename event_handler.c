/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:38 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/05 11:10:59 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "event_handler.h"
#include <stdio.h>

// int	close_window(t_img *data)
// {
// 	mlx_loop_end(data->mlx_ptr);
// 	return (1);
// }

int	key_handle(int keycode, t_scene *scene)
{
	t_img	*data;

	data = scene->img;
	if (keycode == ESC)
		free_img(data);
	else if (keycode == PLUS)
		scene->ambient.lighting_ratio += 0.1;
	else if (keycode == MINUS)
		scene->ambient.lighting_ratio -= 0.1;
	else if (keycode == UP)
		scene->camera.pos.y += CAM_PACE;
	else if (keycode == DOWN)
		scene->camera.pos.y -= CAM_PACE;
	else if (keycode == LEFT)
		scene->camera.pos.x -= CAM_PACE;
	else if (keycode == RIGHT)
		scene->camera.pos.x += CAM_PACE;
	else
		ft_printf("KeyCode: %d\n", keycode);
	if (keycode != ESC)
		draw(scene);
	return (0);
}

int	mouse_handle(int button, int x, int y, t_scene *scene)
{
	t_img	*data;

	(void) x;
	(void) y;
	data = scene->img;
	if (button == WHEEL_UP)
		scene->camera.pos.z -= CAM_PACE;
	else if (button == WHEEL_DOWN)
		scene->camera.pos.z += CAM_PACE;
	draw(scene);
	return (0);
}
