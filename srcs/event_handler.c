/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:38 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/04 15:59:58 by tvasilev         ###   ########.fr       */
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
		scene->camera.pos.z += CAM_PACE;
	else if (keycode == DOWN)
		scene->camera.pos.z -= CAM_PACE;
	else if (keycode == LEFT)
		scene->camera.pos.x -= CAM_PACE;
	else if (keycode == RIGHT)
		scene->camera.pos.x += CAM_PACE;
	else if (keycode == Q)
		scene->camera.orientation.z -= ORIENT_PACE;
	else if (keycode == E)
		scene->camera.orientation.z += ORIENT_PACE;
	else if (keycode == W)
		scene->camera.orientation.y -= ORIENT_PACE;
	else if (keycode == S)
		scene->camera.orientation.y += ORIENT_PACE;
	else if (keycode == A)
		scene->camera.orientation.x += ORIENT_PACE;
	else if (keycode == D)
		scene->camera.orientation.x -= ORIENT_PACE;
	else
		ft_printf("KeyCode: %d\n", keycode);
	if (keycode != ESC)
		draw(scene);
	return (0);
}

int	track_delta(int button, int x, int y, t_scene *scene)
{
	t_camera	*c;

	(void) x;
	(void) y;
	(void) button;
	c = &scene->camera;
	// if (button == LEFT_BUTTON)
	// {
	// 	// H : 1 = d : x
	// 	// printf("Dist: %f %f\n", (x - c->delta.x) / HEIGHT, (c->delta.y - y) / HEIGHT);
	// 	c->orientation.x += (x - c->delta.x) / HEIGHT;
	// 	c->orientation.y += (c->delta.y - y) / HEIGHT;
	// 	c->delta = (t_point_2d){0, 0};
	// 	draw(scene);
	// }
	return (0);
}

int	mouse_handle(int button, int x, int y, t_scene *scene)
{
	t_img	*data;

	(void) x;
	(void) y;
	data = scene->img;
	if (button == WHEEL_UP)
		scene->camera.fov -= 1;
	if (button == WHEEL_DOWN)
		scene->camera.fov += 1;
	// if (button == LEFT_BUTTON)
	// 	scene->camera.delta = (t_point_2d){x, y};
	if (button != LEFT_BUTTON)
		draw(scene);
	return (0);
}
