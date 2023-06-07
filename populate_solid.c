/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_solid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:31:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/07 13:04:13 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_sphere(t_scene *scene, char **el)
{
	t_sphere	sp;
	static int	i = 0;

	if (i == MAX_SOLID)
		return (ft_warning("not handling these many solids", \
				NULL, INVALID_FILE));
	if (ft_arrlen(el) != 4)
		return (ft_warning("Sphere expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (ft_isfloat(el[2]) && ft_atof(el[2]) > 0
		&& extract_xyz(el[1], &sp.pos) == SUCCESS
		&& extract_rgb(el[3], &sp.trgb) == SUCCESS)
	{
		sp.diameter = ft_atof(el[2]);
		scene->sp[i] = sp;
		printf("sphere %d: %p\n", i, &scene->sp[i]);
		i++;
		return (SUCCESS);
	}
	return (ft_warning("sphere", "invalid argument", INVALID_ELEMENT));
}

int	validate_plane(t_scene *scene, char **el)
{
	t_plane		pl;
	static int	i = 0;

	if (i == MAX_SOLID)
		return (ft_warning("not handling these many solids", \
				NULL, INVALID_FILE));
	if (ft_arrlen(el) != 4)
		return (ft_warning("Plane expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	if (extract_xyz(el[1], &pl.pos)
		|| extract_xyz(el[2], &pl.rotation)
		|| !validate_3d_range((t_point_3d)pl.rotation, -1.0, 1.0)
		|| extract_rgb(el[3], &pl.trgb))
		return (ft_warning("invalid argument: ", el[2], \
					INVALID_ELEMENT));
	scene->pl[i] = pl;
	i++;
	return (SUCCESS);
}

int	validate_cylinder(t_scene *scene, char **el)
{
	t_cylinder	cy;
	static int	i = 0;

	if (i == MAX_SOLID)
		return (ft_warning("not handling these many solids", \
				NULL, INVALID_FILE));
	if (ft_arrlen(el) != 6)
		return (ft_warning("Cylinder expects 5 parameters", \
				NULL, INVALID_ELEMENT));
	if (extract_xyz(el[1], &cy.center)
		|| extract_xyz(el[2], &cy.rotation)
		|| !validate_3d_range(cy.rotation, -1.0, 1.0)
		|| extract_rgb(el[5], &cy.trgb))
		return (ft_warning("invalid argument", el[2], \
					INVALID_ELEMENT));
	if (ft_isfloat(el[3]) && ft_isfloat(el[4]))
	{
		cy.diameter = ft_atof(el[3]);
		cy.height = ft_atof(el[4]);
		if (cy.diameter <= 0 || cy.height <= 0)
			return (ft_warning("invalid argument", \
					NULL, INVALID_ELEMENT));
	}
	scene->cy[i] = cy;
	i++;
	return (SUCCESS);
}
