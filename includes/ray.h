/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:12:45 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/21 11:03:45 by tfregni          ###   ########.fr       */
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

typedef struct s_scene	t_scene;

t_ray		ray(t_point3 origin, t_vec3 direction);
t_point3	ray_at(t_ray ray, double t);
t_color		ray_color(t_scene *scene, t_ray r);

#endif
