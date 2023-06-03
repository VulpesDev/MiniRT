/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:21:19 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/03 12:45:50 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "event_handler.h"

int	mlx_manage(t_img *data)
{

	//mouse hook
	//key hook
	mlx_key_hook(data->win_ptr, &key_handle, data);
	//any other special hooks
	mlx_hook(data->win_ptr, X_BUTTON, 0, &close_window, data);
	//loop
	mlx_loop(data->mlx_ptr);
	//3x destroy
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_display(data->mlx_ptr);
	//free mlx
	free(data->mlx_ptr);
	return (1);
}

int	main(void)
{
	t_img	data;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");

	data.mlx_ptr = mlx;
	data.win_ptr = mlx_win;
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);
	mlx_manage(&data);
	return (1);
}