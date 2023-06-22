/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:52 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/17 16:15:53 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H
# include <stdbool.h>
# include "vec3.h"

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	int			trgb;
	t_color		color;
}				t_hit_record;

#endif
