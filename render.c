/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/03 21:19:02 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_err	init_img(t_scene *scene)
{
	t_img	*data;

	scene->img = malloc(sizeof(t_img));
	if (!scene->img)
		return (MEM_FAIL);
	data = scene->img;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
									&data->line_len, &data->endian);
	return (SUCCESS);
}

t_err	render_scene(t_scene *scene)
{
	if (!init_img(scene))
		mlx_manage(scene->img);
	return (SUCCESS);
}
