/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:05:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/14 10:45:24 by tfregni          ###   ########.fr       */
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

t_matrix	create_matrix(const float mx[4][4], size_t size)
{
	t_matrix	m;

	m.size = size;
	ft_memmove(m.matrix, mx, sizeof(float) * 16);
	return (m);
}

t_matrix	mx_get_identity(void)
{
	const float	mx[4][4] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
	};
	t_matrix	m;

	m = create_matrix(mx, 16);
	return (m);
}

t_point_3d	mx_mult(t_matrix m, t_point_3d p)
{
	t_point_3d	ret;
	float		w;

	w = p.x * m.matrix[0][3] + p.y * m.matrix[1][3] + \
			p.z * m.matrix[2][3] + m.matrix[3][3];
	ret.x = (p.x * m.matrix[0][0] + p.y * m.matrix[1][0] + \
			p.z * m.matrix[2][0] + m.matrix[3][0]);
	ret.y = (p.x * m.matrix[0][1] + p.y * m.matrix[1][1] + \
			p.z * m.matrix[2][1] + m.matrix[3][1]);
	ret.z = (p.x * m.matrix[0][2] + p.y * m.matrix[1][2] + \
			p.z * m.matrix[2][2] + m.matrix[3][2]);
	if (w != 1)
	{
		ret.x = ret.x / w;
		ret.y = ret.y / w;
		ret.z = ret.z / w;
	}
	return (ret);
}

t_matrix	mx_cross(t_matrix a, t_matrix b)
{
	float		m[4][4];
	size_t		row;
	size_t		col;

	ft_bzero(m, sizeof(float) * 16);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			m[row][col] = a.matrix[row][0] * b.matrix[0][col]
				+ a.matrix[row][1] * b.matrix[1][col]
				+ a.matrix[row][2] * b.matrix[2][col]
				+ a.matrix[row][3] * b.matrix[3][col];
		}
	}
	return (create_matrix(m, 4));
}

/**
 * Rx = [ 1       0        0       0 ;
       0    cos(α)   sin(α)   0 ;
       0   -sin(α)   cos(α)   0 ;
       0       0        0       1 ]
*/
t_matrix	mx_rotate_x(t_matrix mx, float x)
{
	const float	mx_rx[4][4] = {
	{1, 0, 0, 0},
	{0, cos(x * M_PI), sin(x * M_PI), 0},
	{0, -sin(x * M_PI), cos(x * M_PI), 0},
	{0, 0, 0, 1}
	};
	t_matrix	cross;

	cross = mx_cross(mx, create_matrix(mx_rx, 16));
	return (cross);
}

/**
Ry = [  cos(β)   0   -sin(β)   0 ;
          0      1       0      0 ;
       sin(β)    0    cos(β)   0 ;
          0      0       0      1 ]
*/
t_matrix	mx_rotate_y(t_matrix mx, float y)
{
	const float	mx_ry[4][4] = {
	{cos(y * M_PI), 0, -sin(y * M_PI), 0},
	{0, 1, 0, 0},
	{sin(y * M_PI), 0, cos(y * M_PI), 0},
	{0, 0, 0, 1}
	};
	t_matrix	cross;

	cross = mx_cross(mx, create_matrix(mx_ry, 16));
	return (cross);
}

/**
Rz = [ cos(γ)    sin(γ)   0   0 ;
      -sin(γ)    cos(γ)   0   0 ;
          0         0      1   0 ;
          0         0      0   1 ]
*/
t_matrix	mx_rotate_z(t_matrix mx, float z)
{
	const float	mx_rz[4][4] = {
	{cos(z * M_PI), sin(z * M_PI), 0, 0},
	{-sin(z * M_PI), cos(z * M_PI), 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
	};
	t_matrix	cross;

	cross = mx_cross(mx, create_matrix(mx_rz, 16));
	return (cross);
}

t_matrix	mx_transl(t_matrix mx, t_point_3d p)
{
	const float	mx_tr[4][4] = {
	{1, 0, 0, p.x},
	{0, 1, 0, p.y},
	{0, 0, 1, p.z},
	{0, 0, 0, 1}
	};
	t_matrix	cross;

	cross = mx_cross(mx, create_matrix(mx_tr, 16));
	return (cross);
}

t_matrix	mx_combine(t_matrix mx, t_vector orient)
{
	t_matrix	comb;

	comb = mx;
	comb = mx_rotate_x(comb, orient.x);
	comb = mx_rotate_y(comb, orient.y);
	comb = mx_rotate_z(comb, orient.z);
	return (comb);
}
