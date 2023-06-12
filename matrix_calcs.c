/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:05:50 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/12 19:44:32 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix_math.h"

/**
 * @param	p 3D point. Its 4th dimension is implicitly set to 1
 *			m 4x4: matrix
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

static t_matrix	orient_xform(t_vector forward, t_vector left, t_vector true_up)
{
	const double	table[MAX][MAX] = {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(table, MAX));
}
