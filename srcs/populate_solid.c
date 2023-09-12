/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_solid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:31:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/10 16:13:27 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

void	init_sphere(t_scene *scene, t_shape *shape)
{
	shape->intersect = intersect_sphere;
	shape->hit = sp_hit;
	shape->normal = sp_normal;
	shape->color = convert_color(shape->trgb);
	shape->is_inside = sp_is_inside;
	scene->shape[scene->shape_count] = *shape;
}

int	validate_sphere(t_scene *scene, char **el)
{
	t_shape		shape;
	int			i;

	i = scene->shape_count;
	if (i >= MAX_SOLID)
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
		init_sphere(scene, &shape);
		return (SUCCESS);
	}
	return (ft_warning("sphere", "invalid argument", INVALID_ELEMENT));
}

int	validate_plane(t_scene *scene, char **el)
{
	t_shape		shape;
	int			i;

	i = scene->shape_count;
	if (i >= MAX_SOLID)
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
	shape.hit = pl_hit;
	shape.normal = pl_normal;
	shape.is_inside = pl_is_inside;
	shape.color = convert_color(shape.trgb);
	scene->shape[i] = shape;
	return (SUCCESS);
}

void	init_cylinder(t_scene *scene, t_shape *shape)
{
	if (vec3_len_squared(shape->rotation) == 0)
		shape->rotation = vec3(0, 1, 0);
	shape->rotation = vec3_unit(shape->rotation);
	shape->is_inside = cy_is_inside;
	shape->intersect = intersect_cylinder;
	shape->hit = cy_hit;
	shape->color = convert_color(shape->trgb);
	scene->shape[scene->shape_count] = *shape;
}

int	validate_cylinder(t_scene *scene, char **el)
{
	t_shape		shape;

	if (scene->shape_count >= MAX_SOLID)
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
	init_cylinder(scene, &shape);
	return (SUCCESS);
}
