/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:18:34 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/16 23:21:15 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "minirt.h"

int	apply_lighting_ratio(int trgb, float lighting_ratio)
{
	return (create_trgb(0, \
			lighting_ratio * ((trgb >> 16) & 0xFF),
			lighting_ratio * ((trgb >> 8) & 0xFF),
			lighting_ratio * (trgb & 0xFF)));
}

t_color	apply_light_to_color(t_color c, double light)
{
	t_color	ret;

	ret = color(0.0, c.r * light, c.g * light, c.b * light);
	ret.r = ft_fmin(ret.r, 1.0f);
	ret.g = ft_fmin(ret.g, 1.0f);
	ret.b = ft_fmin(ret.b, 1.0f);
	return (ret);
}

/**
 * @brief converts an int in trgb format to a color struct with double values
 * in range [0, 1]
 * @param trgb int in trgb format
 * @return color struct
*/
t_color	convert_color(int trgb)
{
	t_color	c;

	c.t = ((trgb >> 24) & 0xFF) / 255.999;
	c.r = ((trgb >> 16) & 0xFF) / 255.999;
	c.g = ((trgb >> 8) & 0xFF) / 255.999;
	c.b = (trgb & 0xFF) / 255.999;
	return (c);
}

/**
 * @brief converts a color struct with double values in range [0, 1]
 * to an int in trgb format
 * @param c color struct
 * @return int in trgb format
*/
int	convert_trgb(t_color c)
{
	int		t;
	int		r;
	int		g;
	int		b;

	t = (int)(c.t * 255.999);
	r = (int)(c.r * 255.999);
	g = (int)(c.g * 255.999);
	b = (int)(c.b * 255.999);
	return (t << 24 | r << 16 | g << 8 | b);
}
