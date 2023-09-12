/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_inside.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:14:07 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/12 19:05:33 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vec3.h"
#include "minirt.h"

bool	sp_is_inside(t_shape *s, t_point_3d cam)
{
	return (vec3_len(vec3_sub(cam, s->sp.pos)) < s->sp.diameter / 2);
}


bool	pl_is_inside(t_shape *s, t_point_3d cam)
{
	(void) s;
	(void) cam;
	return (false);
}

bool	cy_is_inside(t_shape *s, t_point_3d cam)
{
	const t_vec3		perpen_vec = vec3_cross(s->cy.rotation, \
		vec3_sub(s->cy.center, cam));
	const double		perpen_len = vec3_len(perpen_vec);
	const double		denom = vec3_dot(s->cy.rotation, s->cy.rotation);
	double				height;

	height = 0.0;
	if (denom > EPSILON)
		height = vec3_dot(vec3_sub(cam, s->cy.center), s->cy.rotation) / denom;
	if (perpen_len <= s->cy.diameter * 0.5f && height >= 0
		&& height <= s->cy.height)
		return (true);
	return (false);
}

t_shape	*check_inside(t_scene *s)
{
	int	i;

	i = s->shape_count;
	while (--i >= 0)
	{
		if (s->shape[i].is_inside(s->shape + i, s->camera.pos))
			return (&s->shape[i]);
	}
	return (NULL);
}
