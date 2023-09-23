/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_mac.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:38 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/23 13:04:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "event_handler.h"
#include <stdio.h>

void	cam_pos(int keycode, t_scene *scene)
{
	if (keycode == PLUS)
		scene->camera.pos.z += CAM_PACE;
	else if (keycode == MINUS)
		scene->camera.pos.z -= CAM_PACE;
	else if (keycode == UP)
		scene->camera.pos.y += CAM_PACE;
	else if (keycode == DOWN)
		scene->camera.pos.y -= CAM_PACE;
	else if (keycode == LEFT)
		scene->camera.pos.x -= CAM_PACE;
	else if (keycode == RIGHT)
		scene->camera.pos.x += CAM_PACE;
}

void	cam_orient(int keycode, t_scene *scene)
{
	if (keycode == Q)
		scene->camera.orientation.z -= ORIENT_PACE;
	else if (keycode == E)
		scene->camera.orientation.z += ORIENT_PACE;
	else if (keycode == W)
		scene->camera.orientation.y += ORIENT_PACE;
	else if (keycode == S)
		scene->camera.orientation.y -= ORIENT_PACE;
	else if (keycode == A)
		scene->camera.orientation.x -= ORIENT_PACE;
	else if (keycode == D)
		scene->camera.orientation.x += ORIENT_PACE;
}

void	ambient_light(int keycode, t_scene *scene)
{
	if (keycode == R)
	{
		scene->ambient.lighting_ratio += LIGHT_PACE;
		if (scene->ambient.lighting_ratio > 1)
			scene->ambient.lighting_ratio = 1;
	}
	else if (keycode == F)
	{
		scene->ambient.lighting_ratio -= LIGHT_PACE;
		if (scene->ambient.lighting_ratio < 0)
			scene->ambient.lighting_ratio = 0;
	}
}

int	key_handle(int keycode, t_scene *scene)
{
	t_img	*data;

	data = scene->img;
	if (keycode == ESC)
		free_img(data);
	else if (keycode == PLUS || keycode == MINUS || keycode == UP
		|| keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		cam_pos(keycode, scene);
	else if (keycode == Q || keycode == E || keycode == W
		|| keycode == S || keycode == A || keycode == D)
		cam_orient(keycode, scene);
	else if (keycode == R || keycode == F)
		ambient_light(keycode, scene);
	if (keycode != ESC)
		draw(scene);
	return (0);
}

int	mouse_handle(int button, int x, int y, t_scene *scene)
{
	(void) x;
	(void) y;
	if (button == WHEEL_UP)
		scene->camera.fov -= 1;
	if (button == WHEEL_DOWN)
		scene->camera.fov += 1;
	if (button != LEFT_BUTTON)
		draw(scene);
	return (0);
}
