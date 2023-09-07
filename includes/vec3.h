/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:40:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/07 11:46:52 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_point_3d;
typedef t_vec3	t_vector;

typedef struct s_color
{
	double	t;
	double	r;
	double	g;
	double	b;
}			t_color;

t_vec3		vec3(double x, double y, double z);
t_vec3		vec3_sum(t_vec3 a, t_vec3 b);
t_vec3		vec3_mult(t_vec3 a, double b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_div(t_vec3 a, double b);
double		vec3_len_squared(t_vec3 a);
double		vec3_len(t_vec3 a);
t_vec3		vec3_unit(t_vec3 a);
t_vec3		vec3_inv(t_vec3 a);
void		vec3_print(t_vec3 a);
t_vec3		vec3_reflect(t_vec3 l, t_vec3 n);

t_point3	point(double x, double y, double z);

t_color		color(double t, double r, double g, double b);
#endif
