/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:52 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/02 12:41:10 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * Given a string, it splits by the ',' and extracts 3 int that
 * assigns bitwise to an int to return (setting transparency to 0)
 * In case of error it exits
*/
int	extract_rgb(char *rgb)
{
	char	**split_arg;
	int		i;
	int		ret;

	split_arg = ft_split(rgb, ',');
	// ft_print_strarr(split_arg);
	if (ft_arrlen(split_arg) == 3)
	{
		i = 0;
		while (i < 3)
		{
			if (ft_atoi(split_arg[i]) < 0 || ft_atoi(split_arg[i]) > 255)
			{
				free(split_arg);
				return (ft_error("minirt: invalid argument", \
						split_arg[i], INVALID_ELEMENT));
			}
			i++;
		}
		ret = create_trgb(0, ft_atoi(split_arg[0]), \
							ft_atoi(split_arg[1]), \
							ft_atoi(split_arg[2]));
		free(split_arg);
		return (ret);
	}
	free(split_arg);
	return (ft_error("minirt: invalid argument", \
						rgb, INVALID_ELEMENT));
}

/**
 * Given a string it splits it by the ',' and extracts 3 floating point
 * values that assigns to a t_point element to return. If any error
 * occurs, it calls ft_error which exits the program.
*/
t_point	extract_xyz(char *xyz)
{
	char	**split_arg;
	int		i;
	t_point	point;

	split_arg = ft_split(xyz, ',');
	if (ft_arrlen(split_arg) == 3)
	{
		i = 0;
		while (i < 3)
		{
			if (!ft_isfloat(split_arg[i]))
				return (ft_error("minirt: expected floating point value", \
							NULL, INVALID_ELEMENT), (t_point){0, 0, 0});
			i++;
		}
		point.x = ft_atof(split_arg[0]);
		point.y = ft_atof(split_arg[1]);
		point.z = ft_atof(split_arg[2]);
		free(split_arg);
		return (point);
	}
	free(split_arg);
	return (ft_error("minirt: invalid argument", xyz, INVALID_ELEMENT), \
						(t_point){0, 0, 0});
}

/**
 * It checks that every parameter of the given struct is in the given range
*/
int	validate_3d_range(t_point point, float min, float max)
{
	if ((point.x < min || point.x > max)
		|| (point.y < min || point.y > max)
		|| (point.z < min || point.z > max))
		return (0);
	return (1);
}
