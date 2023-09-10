/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:33:39 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/10 16:33:36 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "minirt.h"

void	calculate_t(double t[], double a, double b, double discriminant);

void	calculate_m(double tm[][3], t_vec3 dir, t_vec3 rot, t_vec3 X);

void	determine_t_m(double t[], double m[], double height);

bool	cy_hit_body(t_shape *shape, t_ray r, t_hit_record *rec);

int		intersect_body(t_scene *scene, t_ray r, float *t, int i);

bool	hit_plane_cap(t_shape *shape, t_ray r, t_hit_record *rec, bool top);

bool	intersect_plane_cap(t_shape *shape, t_ray r, float *t, bool top);

#endif