/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 08:25:02 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/03 21:02:48 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "event_handler.h"

// int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

int	free_img(t_img *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data = NULL;
	exit(0);
	return (0);
}

int	mlx_manage(t_img *data)
{
	mlx_key_hook(data->win_ptr, &key_handle, data);
	mlx_hook(data->win_ptr, ON_DESTROY, 0, &free_img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	mlx_loop(data->mlx_ptr);
	free_img(data);
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
