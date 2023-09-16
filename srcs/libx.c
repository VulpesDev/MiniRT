/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 08:25:02 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/16 14:29:27 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "event_handler.h"

int	free_img(t_img *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data = NULL;
	// exit(0);
	return (0);
}

int	mlx_manage(t_scene *scene)
{
	t_img	*data;

	data = scene->img;
	mlx_key_hook(data->win_ptr, &key_handle, scene);
	mlx_mouse_hook(data->win_ptr, &mouse_handle, scene);
	// mlx_hook(data->win_ptr, ON_MOUSEUP, (1L << 3), &track_delta, scene);
	mlx_hook(data->win_ptr, ON_DESTROY, 0, &free_img, data);
	mlx_loop(data->mlx_ptr);
	free_img(data);
	free(data);
	return (1);
}

void	my_mlx_pixel_put_d(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

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
