/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:05:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/13 10:34:59 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix_math.h"

/**
 * @param	p 3D point. Its 4th dimension is implicitly set to 1
 * @param	m 4x4: matrix
 * @returns	a transformed 3D point
*/
t_point_3d	transform(t_point_3d p, t_matrix_trans m)
{
	t_point_3d	ret;
	float		w;

	w = p.x * m[0][3] + p.y * m[1][3] + p.z * m[2][3] + m[3][3];
	ret.x = (p.x * m[0][0] + p.y * m[1][0] + p.z * m[2][0] + m[3][0]);
	ret.y = (p.x * m[0][1] + p.y * m[1][1] + p.z * m[2][1] + m[3][1]);
	ret.z = (p.x * m[0][2] + p.y * m[1][2] + p.z * m[2][2] + m[3][2]);
	if (w != 1)
	{
		ret.x = ret.x / w;
		ret.y = ret.y / w;
		ret.z = ret.z / w;
	}
	return (ret);
}

t_matrix	orient_xform(t_vector forward, t_vector left, t_vector true_up)
{
	const double	table[4][4] = {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(table, 4));
}

t_matrix	get_identity_matrix(void)
{
	const double	table_id[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(table_id, MAX));
}

t_matrix	translation(double x, double y, double z)
{
	const double	transl[MAX][MAX] = {
	{1, 0, 0, x},
	{0, 1, 0, y},
	{0, 0, 1, z},
	{0, 0, 0, 1},
	};

	return (create_matrix(transl, MAX));
}

t_matrix	scaling(double x, double y, double z)
{
	const double	scale[MAX][MAX] = {
	{x, 0, 0, 0},
	{0, y, 0, 0},
	{0, 0, z, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(scale, MAX));
}

t_matrix	shearing(t_shearing x, t_shearing y, t_shearing z)
{
	const double	shear[MAX][MAX] = {
	{1, x.p1, x.p2, 0},
	{y.p1, 1, y.p2, 0},
	{z.p1, z.p2, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(shear, MAX));
}

void	calculate_rotation_angles(t_vector vec, double *x, double *z);

t_matrix	rotation_matrix(t_vector vector)
{
	double		x_angle;
	double		z_angle;
	t_matrix	rotate_z;
	t_matrix	rotate_x;
	t_matrix	full_rotation;

	calculate_rotation_angles(vector, &x_angle, &z_angle);
	rotate_z = rotation_z(z_angle);
	rotate_x = rotation_x(x_angle);
	full_rotation = multiply_mx_mx(rotate_z, rotate_x);
	return (full_rotation);
}

/**
 * @brief Calculates the rotation angles for a given vector.
 *
 * @param vec The vector for which the rotation angles will be calculated.
 * @param x A pointer to the variable that will store the rotation angle
 *          around the x-axis.
 * @param z A pointer to the variable that will store the rotation angle
 *          around the z-axis.
 */
void	calculate_rotation_angles(t_vector vec, double *x, double *z)
{
	double	ratio;

	ratio = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (0.0 == ratio)
		*z = M_PI_2;
	else
		*z = acos(vec.y / ratio);
	*x = acos(ratio);
}

t_matrix	rotation_x(double rad)
{
	const double	sine = sin(rad);
	const double	cosine = cos(rad);
	const double	rotate[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, cosine, -sine, 0},
	{0, sine, cosine, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	rotation_y(double rad)
{
	const double	sine = sin(rad);
	const double	cosine = cos(rad);
	const double	rotate[MAX][MAX] = {
	{cosine, 0, sine, 0},
	{0, 1, 0, 0},
	{-sine, 0, cosine, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	rotation_z(double rad)
{
	const double	sine = sin(rad);
	const double	cosine = cos(rad);
	const double	rotate[MAX][MAX] = {
	{cosine, -sine, 0, 0},
	{sine, cosine, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	multiply_mx_mx(t_matrix a, t_matrix b)
{
	double		m[MAX][MAX];
	size_t		row;
	size_t		col;

	ft_bzero(m, sizeof(double) * SIZE);
	row = -1;
	while (++row < MAX)
	{
		col = -1;
		while (++col < MAX)
		{
			m[row][col] = a.matrix[row][0] * b.matrix[0][col]
				+ a.matrix[row][1] * b.matrix[1][col]
				+ a.matrix[row][2] * b.matrix[2][col]
				+ a.matrix[row][3] * b.matrix[3][col];
		}
	}
	return (create_matrix(m, MAX));
}

t_tuple	tuple(double x, double y, double z, double w)
{
	return ((t_tuple){x, y, z, w});
}

t_tuple	multiply_tp_mx(t_matrix a, t_tuple b)
{
	double		t[MAX];
	size_t		row;

	row = -1;
	while (++row < MAX)
	{
		t[row] = a.matrix[row][0] * b.x \
			+ a.matrix[row][1] * b.y \
			+ a.matrix[row][2] * b.z \
			+ a.matrix[row][3] * b.w;
	}
	return (tuple(t[0], t[1], t[2], t[3]));
}

t_matrix	transpose(t_matrix	t)
{
	size_t		row;
	size_t		col;
	double		m[MAX][MAX];

	row = -1;
	while (++row < t.size)
	{
		col = -1;
		while (++col < t.size)
			m[col][row] = t.matrix[row][col];
	}
	return (create_matrix(m, t.size));
}

t_bool	is_invertible(t_matrix t)
{
	if (get_determinant(t) == 0)
		return (FALSE);
	return (TRUE);
}

t_matrix	inverse(t_matrix t)
{
	double	inverted[MAX][MAX];
	double	determinant;
	size_t	row;
	size_t	col;

	if (!is_invertible(t))
		return (get_identity_matrix());
	determinant = get_determinant(t);
	row = -1;
	while (++row < t.size)
	{
		col = -1;
		while (++col < t.size)
			inverted[col][row] = \
				get_cofactor(t, row, col) / determinant;
	}
	return (create_matrix(inverted, MAX));
}
