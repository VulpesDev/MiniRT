/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:06:27 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/13 10:32:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_MATH_H
# define MATRIX_MATH_H
# include "minirt.h"
# define MAX 4
# define SIZE 16

typedef float	t_matrix_trans[4][4];

typedef struct s_shearing
{
	double	p1;
	double	p2;
}			t_shearing;

/**
 * @brief Tuple means a list of ordered things. The struct t_tuple stores
 * coordinates for a left-handed coordinate system, i.e, the thumb of your left
 * hand points to x in the right direction, the fingers point to y and curling
 * the fingers towards the palm point to z.
 *
 * @param x Represents the value of the x-axis coordinate.
 * @param y Represents the value of the y-axis coordinate.
 * @param z Represents the value of the z-axis coordinate.
 * @param w Distinguishes the t_tuple between a vector or a point. If w = 0,
 * then the tuple is a vector. Otherwise, if w = 1, the tuple is a point.
 */
typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

t_point_3d	transform(t_point_3d p, t_matrix_trans m);
t_matrix	orient_xform(t_vector forward, t_vector left, t_vector true_up);
t_matrix	create_matrix(const double table[4][4], size_t size);
t_matrix	get_identity_matrix(void);
t_matrix	translation(double x, double y, double z);
t_matrix	scaling(double x, double y, double z);
t_matrix	shearing(t_shearing x, t_shearing y, t_shearing z);
t_matrix	rotation_matrix(t_vector vector);
void	calculate_rotation_angles(t_vector vec, double *x, double *z);
t_matrix	rotation_x(double rad);
t_matrix	rotation_y(double rad);
t_matrix	rotation_z(double rad);
t_matrix	multiply_mx_mx(t_matrix a, t_matrix b);
t_tuple		multiply_tp_mx(t_matrix a, t_tuple b);
t_matrix	transpose(t_matrix	t);
t_matrix	inverse(t_matrix t);
double		get_determinant(t_matrix t);
double		get_cofactor(t_matrix t, size_t row, size_t col);
t_matrix	get_submatrix(t_matrix t, size_t del_row, size_t del_col);
t_tuple		create_point(float x, float y, float z);
#endif
