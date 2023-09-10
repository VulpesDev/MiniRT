/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_inside.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:14:07 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/10 13:48:05 by tvasilev         ###   ########.fr       */
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
	const t_vec3 perpen_vec = vec3_cross(s->rotation, vec3_sub(s->cy.center, cam));
	const float perpen_len = vec3_len(perpen_vec);
	const float denom = vec3_dot(s->rotation, s->rotation);
	float height = 0.0;

	if (denom > EPSILON)
		height = vec3_dot(vec3_sub(cam, s->cy.center), s->rotation) / denom;	
	
	//?Debug
	// printf("rotation: (%f, %f, %f)\n", s->rotation.x, s->rotation.y, s->rotation.z);
	// printf("sub: (%f, %f, %f)\n", vec3_sub(s->cy.center, cam).x, vec3_sub(s->cy.center, cam).y, vec3_sub(s->cy.center, cam).z);
	// printf("height: %f\n", height);
	// printf("perpen_len: %f\n", perpen_len);
	//?Debug

	if (perpen_len <= s->cy.diameter * 0.5f && height >= 0 && height <= s->cy.height)
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
