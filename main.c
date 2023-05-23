/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:42:10 by tfregni           #+#    #+#             */
/*   Updated: 2023/05/23 16:50:52 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(char *msg, char *arg)
{
	ft_putstr_fd(msg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putchar_fd('\n', 2);
}

int	main(int ac, char **av)
{
	(void) av;
	if (ac != 2)
	{
		ft_error("miniRT", "bad arguments");
		return (1);
	}
	return (0);
}
