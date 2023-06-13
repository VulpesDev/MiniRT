/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:55:47 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/13 10:01:21 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_math.h"
#include "minirt.h"

t_matrix	create_matrix(const double table[4][4], size_t size)
{
	t_matrix	mx;

	mx.size = size;
	ft_memmove(mx.matrix, table, sizeof(double) * 16);
	return (mx);
}

double	get_determinant(t_matrix t)
{
	size_t	col;
	double	det;

	det = 0;
	if (t.size == 2)
		det = (t.matrix[0][0] * t.matrix[1][1]) \
			- (t.matrix[0][1] * t.matrix[1][0]);
	else
	{
		col = -1;
		while (++col < t.size)
			det += (t.matrix[0][col] * get_cofactor(t, 0, col));
	}
	return (det);
}

t_matrix	get_submatrix(t_matrix t, size_t del_row, size_t del_col)
{
	double	sub_m[MAX][MAX];
	size_t	row;
	size_t	col;

	row = -1;
	if (t.size == 0)
		return (get_identity_matrix());
	while (++row < t.size - 1)
	{
		col = -1;
		while (++col < t.size - 1)
			sub_m[row][col] = t.matrix \
				[row + (row >= del_row)][col + (col >= del_col)];
	}
	return (create_matrix(sub_m, t.size - 1));
}

double	get_minor(t_matrix t, size_t row, size_t col)
{
	t_matrix	m;
	double		minor;

	m = get_submatrix(t, row, col);
	minor = get_determinant(m);
	return (minor);
}

double	get_cofactor(t_matrix t, size_t row, size_t col)
{
	double		cofactor;

	cofactor = get_minor(t, row, col);
	if ((row + col) % 2 == 1)
		cofactor *= -1;
	return (cofactor);
}

t_tuple	create_point(float x, float y, float z)
{
	return ((t_tuple){x, y, z, 1});
}
