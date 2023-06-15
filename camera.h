/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:39:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/15 14:14:23 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include <stdint.h>
# include "vec3.h"

# define WIDTH 1024
# define HEIGHT 768

typedef struct s_camera
{
	t_point3		pos;
	t_vec3			orientation;
	uint8_t			fov;
	double			viewport_height;
	double			viewport_width;
	double			focal_length;
	t_point3		lower_left_corner;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			vup;
	t_vec3			up;
	t_vec3			right;
}					t_camera;

void	cam_setup(t_camera *c);

#endif
