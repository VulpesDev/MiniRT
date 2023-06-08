/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:30:47 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/09 01:18:25 by tfregni          ###   ########.fr       */
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

void	set_y_range(t_camera *c, float range_x)
{
	float	ratio;
	float	range_y;
	float	mid_y;

	ratio = (float)WIDTH / HEIGHT;
	range_y = range_x * ratio;
	printf("range_x: %f ratio: %f\n", range_x, ratio);
	mid_y = CANV_MIN_Y + (range_y / 2);
	c->min_y = mid_y - (range_y / 2);
	c->max_y = c->min_y + range_y;
}

/**
 * if FOV == 180 the tan explodes
*/
void	set_camera_canvas(t_camera *c)
{
	float	max_range_x;
	float	mid;
	float	fov_rad;

	fov_rad = c->fov * (M_PI / 180);
	// max_range_x = CANV_MAX_X - CANV_MIN_X;
	max_range_x = 2 * tan(fov_rad / 2);
	mid = CANV_MIN_X + (max_range_x / 2);
	printf("range: %f rad: %f mid: %f\n", max_range_x, fov_rad, mid);
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
	printf("w: %i h: %i min_x: %f min_y: %f, fov: %i bot_left: %f, %f top_right: %f, %f\n", WIDTH, HEIGHT, CANV_MIN_X, CANV_MIN_Y, scene->camera.fov, scene->camera.min_x, scene->camera.min_y, scene->camera.max_x, scene->camera.max_y);
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
