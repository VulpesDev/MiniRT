/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:30:47 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/14 17:01:03 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix_math.h"
#include "vector_math.h"

/**
 * @returns 0 for success
*/
t_err	validate_ambient(t_scene *scene, char **el)
{
	if (ft_arrlen(el) != 3)
		return (ft_warning("Ambient expects 2 parameters", \
				NULL, INVALID_ELEMENT));
	if (ft_isfloat(el[1]) && ft_atof(el[1]) >= 0 && ft_atof(el[1]) <= 1
		&& !extract_rgb(el[2], &scene->ambient.trgb))
	{
		scene->ambient.lighting_ratio = ft_atof(el[1]);
		return (SUCCESS);
	}
	return (ft_warning("invalid argument: ", \
			el[1], INVALID_ELEMENT));
}

/**
 * if FOV == 180 the tan explodes
*/
void	set_camera_canvas(t_camera *c)
{
	float	fov_rad;
	float	ratio;

	if (c->fov >= 180)
		c->fov = 179;
	if (c->fov < 0)
		c->fov = 0;
	ratio = (float)WIDTH / HEIGHT;
	fov_rad = c->fov * (M_PI / 180);
	c->viewport_width = 2 * tanf(fov_rad / 2) * CANV_DIST;
	c->viewport_heigth = c->viewport_width  / ratio;
	printf("viewport_w: %f \nviewport_h: %f\n", c->viewport_width, c->viewport_heigth);
	// c->top_right = (t_point_2d){range_x / 2 + c->pos.x, range_y / 2 + c->pos.y};
	// c->bot_left = (t_point_2d){(range_x / 2) * -1 + \
	// 							c->pos.x, -(range_y / 2) + c->pos.y};
	// printf("rad: %f range_x: %f range_y: %f corners: b %f t %f l %f r %f\n", fov_rad, range_x, range_y, c->bot_left.y, c->top_right.y, c->top_right.x, c->bot_left.x);
	// printf("pos: %f %f %f, fov: %d, orient %f %f %f\n", c->pos.x, c->pos.y, c->pos.z, c->fov, c->orientation.x, c->orientation.y, c->orientation.z);
}

void	set_transform_mx(t_camera *c)
{
	c->transform = mx_get_identity();
	print_4x4(c->transform.matrix);
	//c->transform = mx_transl(c->transform, c->pos);
	c->transform = mx_combine(c->transform, c->orientation);
	c->vup = (t_vector){0, 1, 0};
	// t_point_3d look_at = mx_mult(c->transform, (t_point_3d)c->vup);
	t_point_3d look_at = (t_vector){0, 0, 0};
	t_point_3d look_from = c->pos;
	t_vector w = vect_norm(vect_sub(look_at, look_from));
	t_vector u = vect_norm(vect_cross(c->vup, w));
	t_vector v = vect_cross(w, u);
	vect_print("w", w);
	vect_print("u", u);
	vect_print("v", v);
	c->horizontal = vect_mult(u, c->viewport_width);
	c->vertical = vect_mult(v, c->viewport_heigth);
	
	vect_print("Horizontal", c->horizontal);
	vect_print("Vertical", c->vertical);
	c->lower_left_corner = vect_sub(vect_sub(c->pos, vect_dev(c->horizontal, 2)), vect_sub(vect_dev(c->vertical, 2), w));
	vect_print("Lower_left_corner", c->lower_left_corner);

	printf("LookAt: %f %f %f\n", look_at.x, look_at.y, look_at.z);
	// print_4x4(c->transform.matrix);
}

/**
 * @returns 0 for success
*/
t_err	validate_camera(t_scene *scene, char **el)
{
	if (ft_arrlen(el) != 4)
		return (ft_warning("Camera expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (extract_xyz(el[1], &scene->camera.pos)
		|| extract_xyz(el[2], &scene->camera.orientation)
		|| !validate_3d_range((t_point_3d)scene->camera.orientation, -1.0, 1.0))
		return (ft_warning("invalid argument: ", el[2], \
				INVALID_ELEMENT));
	scene->camera.fov = ft_atoi(el[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (ft_warning("invalid argument: ", el[3], \
				INVALID_ELEMENT));
	set_camera_canvas(&scene->camera);
	set_transform_mx(&scene->camera);
	return (SUCCESS);
}

/**
 * @returns 0 for success
*/
t_err	validate_light(t_scene *scene, char **el)
{
	int	arrlen;

	arrlen = ft_arrlen(el);
	if (arrlen > 4 || arrlen < 3)
		return (ft_warning("Light expects 2 or 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (ft_isfloat(el[2]) && ft_atof(el[2]) >= 0 && ft_atof(el[2]) <= 1
		&& extract_xyz(el[1], &scene->light.pos) == SUCCESS)
	{
		scene->light.brightness = ft_atof(el[2]);
		if ((arrlen == 4 && !extract_rgb(el[3], &scene->light.trgb))
			|| arrlen == 3)
			return (SUCCESS);
	}
	return (ft_warning("invalid argument", \
			el[2], INVALID_ELEMENT));
}
