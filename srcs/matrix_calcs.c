/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:05:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 09:39:54 by tfregni          ###   ########.fr       */
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
