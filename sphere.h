/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:11 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/15 16:12:26 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "vec3.h"
# include "ray.h"

typedef struct s_sphere
{
	t_point_3d		pos;
	float			diameter;
	int				trgb;
}					t_sphere;

double	sp_hit(t_point3 center, double diameter, t_ray r);
#endif
