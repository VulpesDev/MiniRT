/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:39:35 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 09:40:12 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix_math.h"

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
