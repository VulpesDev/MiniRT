/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:33:39 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/10 14:52:11 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "minirt.h"

bool	cy_hit_body(t_shape *shape, t_ray r, t_hit_record *rec);

void	calculate_t(double t[], double a, double b, double discriminant);

void	calculate_m(double m[], double t[], t_vec3 dir, t_vec3 rot, t_vec3 X);

void	determine_t_m(double t[], double m[], double height);

int		intersect_body(t_scene *scene, t_ray r, float *t, int i);

#endif