/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:52 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 09:53:21 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief Given a string, it splits by the ',' and extracts 3 int that
 * assigns bitwise to an int to return (setting transparency to 0)
 * @param	string in format "int,int,int"
 *			pointer to the int where to write the rgb
 * @returns 0 for success
*/
t_err	extract_rgb(char *rgb, int *ret)
{
	char	**split_arg;
	int		i;

	split_arg = ft_split(rgb, ',');
	if (split_arg && ft_arrlen(split_arg) == 3)
	{
		i = 0;
		while (i < 3)
		{
			if (ft_atoi(split_arg[i]) < 0 || ft_atoi(split_arg[i]) > 255)
			{
				ft_free_str_arr(split_arg);
				return (ft_warning("invalid argument", \
						rgb, INVALID_ELEMENT));
			}
			i++;
		}
		*ret = create_trgb(0, ft_atoi(split_arg[0]), ft_atoi(split_arg[1]), \
							ft_atoi(split_arg[2]));
		ft_free_str_arr(split_arg);
		return (SUCCESS);
	}
	ft_free_str_arr(split_arg);
	return (ft_warning("invalid argument", rgb, INVALID_ELEMENT));
}

/**
 * @param	string expected in the format float,float,float
 * 			pointer to a t_point_3d structure carrying 3 floats
 * @returns	0 for success, > 0 error code
 * The point structure is populated with the values extracted
 * from the string when validated
*/
t_err	extract_xyz(char *xyz, t_point_3d *point)
{
	char	**split_arg;
	int		i;

	if (!xyz || !point)
		return (MEM_FAIL);
	split_arg = ft_split(xyz, ',');
	if (ft_arrlen(split_arg) == 3)
	{
		i = -1;
		while (++i < 3)
		{
			if (!ft_isfloat(split_arg[i]))
			{
				ft_free_str_arr(split_arg);
				return (ft_warning("expected floating point value", \
							NULL, INVALID_ELEMENT));
			}
		}
		*point = (t_point_3d){ft_atof(split_arg[0]), ft_atof(split_arg[1]), \
			ft_atof(split_arg[2])};
		ft_free_str_arr(split_arg);
		return (SUCCESS);
	}
	ft_free_str_arr(split_arg);
	return (ft_warning("invalid argument", xyz, INVALID_ELEMENT));
}

/**
 * It checks that every parameter of the given struct is in the given range
*/
int	validate_3d_range(t_point_3d point, float min, float max)
{
	if ((point.x < min || point.x > max)
		|| (point.y < min || point.y > max)
		|| (point.z < min || point.z > max))
		return (0);
	return (1);
}
