/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_solid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:31:05 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/02 13:37:54 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_sphere(t_scene *scene, char **el)
{
	t_sphere	sp;
	static int	i = 0;

	if (ft_arrlen(el) != 4)
		return (ft_error("miniRT: Sphere expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	sp.pos = extract_xyz(el[1]);
	if (ft_isfloat(el[2]) && ft_atof(el[2]) > 0)
		sp.diameter = ft_atof(el[2]);
	sp.trgb = extract_rgb(el[3]);

	scene->sp[i] = sp;
	return (1);
}


int	validate_plane(t_scene *scene, char **el)
{
	t_plane		pl;
	static int	i = 0;

	if (ft_arrlen(el) != 4)
		return (ft_error("miniRT: Plane expects 3 parameters", \
				NULL, INVALID_ELEMENT));
	pl.pos = extract_xyz(el[1]);
	pl.rotation = extract_xyz(el[2]);
	pl.trgb = extract_rgb(el[3]);
	scene->pl[i] = pl;
	return (1);
}
