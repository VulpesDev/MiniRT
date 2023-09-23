/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:39:08 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/23 13:07:41 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include <stdint.h>
# include <math.h>
# include "vec3.h"

# define WIDTH 1024
# define HEIGHT 768

typedef struct s_camera
{
	t_point3		pos;
	t_vec3			orientation;
	t_point3		look_at;
	uint8_t			fov;
	double			aspect_ratio;
	double			viewport_height;
	double			viewport_width;
	double			focal_length;
	t_point3		viewport_top_left;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			pxl_size_hor;
	t_vec3			pxl_size_ver;
	t_vec3			vert_up;
	t_vec3			up;
	t_vec3			right;
}					t_camera;

void		cam_setup(t_camera *c);

#endif
