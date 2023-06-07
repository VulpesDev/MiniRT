/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:42:10 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/07 12:55:01 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene **scene)
{
	free((*scene)->sp);
	free((*scene)->pl);
	free((*scene)->cy);
	(*scene)->sp = NULL;
	(*scene)->pl = NULL;
	(*scene)->cy = NULL;
	free(*scene);
	*scene = NULL;
}

/**
 * It throws an error and returns an error code without freeing the scene
 * To be used for errors that don't interrupt the program
*/
t_err	ft_warning(char *msg, char *arg, int err_code)
{
	ft_putstr_fd("miniRT: ", 2);
	ft_putstr_fd(msg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putchar_fd('\n', 2);
	return (err_code);
}

/**
 * It throws an error, frees the scene and returns an error code
 * To be used for fatal errors
*/
t_err	ft_error(char *msg, char *arg, int err_code, t_scene *scene)
{
	ft_putstr_fd("Error\nminiRT: ", 2);
	ft_putstr_fd(msg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putchar_fd('\n', 2);
	free_scene(&scene);
	return (err_code);
}

/**
 * @returns 0 for success, > 0 for err_code
*/
t_err	init_scene(t_scene *scene)
{
	scene->sp = ft_calloc(sizeof(t_sphere), (MAX_SOLID + 1));
	scene->pl = ft_calloc(sizeof(t_plane), (MAX_SOLID + 1));
	scene->cy = ft_calloc(sizeof(t_cylinder), (MAX_SOLID + 1));
	if (!scene->sp || !scene->pl || !scene->cy)
		return (MEM_FAIL);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2)
		return (ft_putendl_fd("miniRT: bad arguments", 2), ARG_REQUIRED);
	scene = malloc(sizeof(t_scene));
	if (!scene || init_scene(scene) != SUCCESS)
		return (ft_putendl_fd("miniRT: memory fail", 2), MEM_FAIL);
	if (parse_args(scene, av[1]))
	{
		free_scene(&scene);
		return (1);
	}
	free_scene(&scene);
	return (0);
}
