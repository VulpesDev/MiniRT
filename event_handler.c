/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:38 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/03 12:41:26 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

int	close_window(t_img *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (1);
}

int	key_handle(int keycode, t_img *data)
{
	if (keycode == ESC)
	{
		close_window(data);
	}
	return (1);
}

// int	mouse_handle(int button, int x, int y, t_img *data)
// {
	
// }