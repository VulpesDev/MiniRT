/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:25:30 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/08 09:13:05 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

/**
 * ray: p = a + bt
 * 	p: a point on the ray
 * 	a: the origin (camera.pos)
 *	b: direction
 *	t: distance along the ray
 * plane: (p - p0)·n = 0
 * 	p0: given point on the plane (pl.pos)
 * 	p: an arbitrary point on the plane
 * 	n: the normal vector
 * The vector between p and p0 is the difference between them
 * This vector lies on the plane and therefore it's perpendicular
 * to the normal. The dot product of perpendicular vectors is 0.
 * If I substitute the ray equation into the plane equation to
 * look for a point that belongs to both
 * (a + bt - p0)·n = 0 which solved for t is
 * ((p0 - a) · n) / b · n
*/
int	intersect_plane(t_scene *scene, t_vector ray_direction, float *t, int i)
{
	float	denominator;
	float	numerator;

	denominator = vect_dot(ray_direction, vect_norm(scene->pl[i].rotation));
	if (denominator > 1e-6)
	{
		numerator = vect_dot(vect_sub(scene->pl[i].pos, scene->camera.pos), vect_norm(scene->pl[i].rotation));
		*t = numerator / denominator;
		return (1);
	}
	return (0);
}
