/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:42:10 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/30 11:23:08 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_err	ft_error(char *msg, char *arg, int err_code)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putchar_fd('\n', 2);
	exit (err_code);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	(void) av;
	if (ac != 2)
		return (ft_error("miniRT", "bad arguments", 1));
	if (parse_args(&scene, av[1]))
		return (1);
	return (0);
}
