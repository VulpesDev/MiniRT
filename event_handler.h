/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:32:50 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/03 16:57:29 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H

# include "minirt.h"

int	close_window(t_img *data);
int	key_handle(int keycode, t_img *data);
int	mouse_handle(int button, int x, int y, t_img *data);

#endif
