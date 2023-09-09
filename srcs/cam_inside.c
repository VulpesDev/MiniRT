/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_inside.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:14:07 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 15:17:07 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
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
	(void) s;
	(void) cam;
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
