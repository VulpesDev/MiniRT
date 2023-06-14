/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:49:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/14 16:00:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "minirt.h"

void		vect_print(char *name, t_vector point);//debugging
t_vector	vect_sum(t_vector a, t_vector b);
t_vector	vect_sub(t_vector a, t_vector b);
float		vect_dot(t_vector a, t_vector b);
t_vector	vect_cross(t_vector u, t_vector v);
t_vector	vect_norm(t_vector v);
float		vect_mag(t_vector v);
t_vector	vect_mult(t_vector v, float a);
t_vector	vect_dev(t_vector v, float a);
t_vector	vect_inverse(t_vector a);

#endif
