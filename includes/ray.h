/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:12:45 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/31 16:21:19 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}			t_ray;

t_ray	ray(t_point3 origin, t_vec3 direction);

t_point3	ray_at(t_ray ray, double t);

#endif
