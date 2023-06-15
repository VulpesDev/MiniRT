/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_solid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:31:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/15 18:08:46 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_sphere(t_scene *scene, char **el)
{
	t_shape		shape;
	int			i;

	i = scene->shape_count;
	if (i == MAX_SOLID)
		return (ft_warning("not handling these many solids", \
				NULL, INVALID_FILE));
	if (ft_arrlen(el) != 4)
		return (ft_warning("Sphere expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (ft_isfloat(el[2]) && ft_atof(el[2]) > 0
		&& extract_xyz(el[1], &shape.sp.pos) == SUCCESS
		&& extract_rgb(el[3], &shape.trgb) == SUCCESS)
	{
		shape.sp.diameter = ft_atof(el[2]);
		// printf("before: sphere %d: %p\n", i, &scene->shape[i]);
		shape.intersect = intersect_sphere;
		shape.hit = sp_hit;
		scene->shape[i] = shape;
		// printf to remove
		printf("sphere %d: %p\n", i, &scene->shape[i]);
		return (SUCCESS);
	}
	return (ft_warning("sphere", "invalid argument", INVALID_ELEMENT));
}

int	validate_plane(t_scene *scene, char **el)
{
	t_shape		shape;
	int			i;

	i = scene->shape_count;
	if (i == MAX_SOLID)
		return (ft_warning("not handling these many solids", \
				NULL, INVALID_FILE));
	if (ft_arrlen(el) != 4)
		return (ft_warning("Plane expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (extract_xyz(el[1], &shape.pl.pos)
		|| extract_xyz(el[2], &shape.rotation)
		|| !validate_3d_range((t_point_3d)shape.rotation, -1.0, 1.0)
		|| extract_rgb(el[3], &shape.trgb))
		return (ft_warning("invalid argument: ", el[2], \
					INVALID_ELEMENT));
	shape.intersect = intersect_plane;
	scene->shape[i] = shape;
	return (SUCCESS);
}

int	validate_cylinder(t_scene *scene, char **el)
{
	t_shape		shape;
	int			i;

	i = scene->shape_count;
	if (i == MAX_SOLID)
		return (ft_warning("not handling these many solids", \
				NULL, INVALID_FILE));
	if (ft_arrlen(el) != 6)
		return (ft_warning("Cylinder expects 5 parameters", \
				NULL, INVALID_ELEMENT));
	if (extract_xyz(el[1], &shape.cy.center)
		|| extract_xyz(el[2], &shape.rotation)
		|| !validate_3d_range(shape.rotation, -1.0, 1.0)
		|| extract_rgb(el[5], &shape.trgb))
		return (ft_warning("invalid argument", el[2], \
					INVALID_ELEMENT));
	if (ft_isfloat(el[3]) && ft_isfloat(el[4]))
	{
		shape.cy.diameter = ft_atof(el[3]);
		shape.cy.height = ft_atof(el[4]);
		if (shape.cy.diameter <= 0 || shape.cy.height <= 0)
			return (ft_warning("invalid argument", \
					NULL, INVALID_ELEMENT));
	}
	scene->shape[i] = shape;
	return (SUCCESS);
}
