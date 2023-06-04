/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:38 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/04 16:48:08 by tfregni          ###   ########.fr       */
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
	else
		ft_printf("KeyCode: %d\n", keycode);
	if (keycode != ESC)
		draw(scene);
	return (0);
}

// int	mouse_handle(int button, int x, int y, t_img *data)
// {

// }
