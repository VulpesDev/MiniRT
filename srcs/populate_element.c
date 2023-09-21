/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:30:47 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/21 09:29:26 by tfregni          ###   ########.fr       */
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
 * @returns 0 for success
*/
t_err	validate_camera(t_scene *scene, char **el)
{
	if (ft_arrlen(el) != 4)
		return (ft_warning("Camera expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (extract_xyz(el[1], &scene->camera.pos)
		|| extract_xyz(el[2], &scene->camera.orientation)
		|| !validate_3d_range((t_point3)scene->camera.orientation, -1.0, 1.0))
		return (ft_warning("invalid argument: ", el[2], \
				INVALID_ELEMENT));
	scene->camera.fov = ft_atoi(el[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (ft_warning("invalid argument: ", el[3], \
				INVALID_ELEMENT));
	scene->camera.focal_length = CANV_DIST;
	scene->camera.vert_up = vec3(0.0f, 1.0f, 0.0f);
	cam_setup(&scene->camera);
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
