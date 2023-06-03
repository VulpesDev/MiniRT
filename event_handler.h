/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:32:50 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/03 12:47:03 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H

# include "minirt.h"

int	close_window(t_img *data);

int	key_handle(int keycode, t_img *data);

int	mouse_handle(int button, int x, int y, t_img *data);

#endif
