/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:06:27 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/09 12:01:30 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_MATH_H
# define MATRIX_MATH_H
# include "minirt.h"

typedef float	t_matrix_trans[4][4];

t_point_3d	transform(t_point_3d p, t_matrix_trans m);

#endif
