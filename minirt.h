/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:43:46 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/25 16:41:28 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "keys.h"
# define SPACE "\t "

typedef enum e_err
{
	ARG_REQUIRED = 1,
	FILE_EXTENSION,
	INVALID_FILE,
	INVALID_ELEMENT,
}			t_err;

int		parse_arg(char *filename);
t_err	ft_error(char *msg, char *arg, int err_code);

#endif
