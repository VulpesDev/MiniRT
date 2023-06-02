/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:43:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/02 12:49:02 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "keys.h"
# define SPACE "\t "
# define HEIGHT 500
# define WIDTH 500

typedef enum e_err
{
	ARG_REQUIRED = 1,
	FILE_EXTENSION,
	INVALID_FILE,
	INVALID_ELEMENT,
}			t_err;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef t_point	t_vector;

int		parse_arg(char *filename);
t_err	ft_error(char *msg, char *arg, int err_code);

#endif
