/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:30:47 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/09 16:22:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	float	range_x;
	float	range_y;
	float	fov_rad;
	float	ratio;

	if (c->fov >= 180)
		c->fov = 179;
	if (c->fov < 0)
		c->fov = 0;
	ratio = (float)WIDTH / HEIGHT;
	fov_rad = c->fov * (M_PI / 180);
	range_x = 2 * tan(fov_rad / 2) * CANV_DIST;
	range_y = range_x / ratio;
	c->top_right = (t_point_2d){range_x / 2 + c->pos.x, range_y / 2 + c->pos.y};
	c->bot_left = (t_point_2d){(range_x / 2) * -1 + \
								c->pos.x, -(range_y / 2) + c->pos.y};
	printf("rad: %f range_x: %f range_y: %f corners: b %f t %f l %f r %f\n", fov_rad, range_x, range_y, c->bot_left.y, c->top_right.y, c->top_right.x, c->bot_left.x);
}

/**
 * Shall we set limits for the position? Maybe macroed in the header file
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
