/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:11 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/17 16:16:26 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "vec3.h"
# include "ray.h"
# include "hittable.h"

typedef struct s_shape	t_shape;
typedef struct s_sphere
{
	t_point_3d		pos;
	float			diameter;
}					t_sphere;

bool	sp_hit(t_shape *shape, t_ray r, t_hit_record *rec);
t_vec3	sp_normal(t_point3 hit, t_point3 center);
#endif
